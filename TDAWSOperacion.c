/*
 * TDAWSOperacion.c
 *
 *  Created on: 16 Oct 2017
 *      Author: Yoel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "TDAWSOperacion.h"
#include "parsers.h"
#include "parseoEntrada.h"

#define path_config "SERVERTP2GRUPAL.conf"

#define MAX_LINEA 255

int inicializarOperacion(TDAWSOperacion *operacion, char *formato, char *nombre) {

	operacion->cRequest = malloc(200);
	if (!operacion->cRequest) return (-1);
	strcpy(operacion->cRequest, "");

	operacion->cResponse = malloc(1000);
	if (!operacion->cResponse) return (-1);
	strcpy(operacion->cResponse, "");

	operacion->cOperacion = malloc(strlen(nombre) + 1);
	if (!operacion->cOperacion) return (-1);
	strcpy(operacion->cOperacion, nombre);

	operacion->dOperacion = malloc(30);
	if (!operacion->dOperacion) return (-1);

	operacion->cFormato = malloc(strlen(formato) + 1);
	if (!operacion->cFormato) return (-1);
	strcpy(operacion->cFormato, formato);

	return (0);
}

int getTime(TDAWS *ws, char *fecha, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "getTime") != 0) return (-1);

	time_t tiempo;
	struct tm * tiempoinfo;
	time(&tiempo);
	tiempoinfo = localtime ( &tiempo );
	strftime(fecha, 26, "%Y/%m/%d %H:%M:%S", tiempoinfo);

	if (strcmp(ws->TOperacion.cFormato, "JSON") == 0) {
		strcpy(operacion->cResponse, "'{\"Time\":\"");
		strcat(operacion->cResponse, fecha);
		strcat(operacion->cResponse, "\"}'\n");
	}
	else {
		strcpy(operacion->cResponse, "<Time>");
		strcat(operacion->cResponse, fecha);
		strcat(operacion->cResponse, "</Time>\n");
	}

	strcpy(operacion->dOperacion, fecha);

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);

	return (0);
}

int getClientById(TDAWS *ws, char por_consola, int id) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	TElemCliente *cliente = malloc(sizeof(TElemCliente));

	char cliente_encontrado = 0;
	char str[4];

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "getClientById") != 0) return (-1);

	if (por_consola == 1)
		strcpy(operacion->cRequest, ws->TOperacion.cRequest);
	else {
		sprintf(str, "%d", id);
		strcpy(operacion->cRequest, str);
	}

	getTime(ws, operacion->dOperacion, 0);

	ls_MoverCorriente(&ws->TClientes, LS_PRIMERO);
	do {
		ls_ElemCorriente(ws->TClientes, cliente);
		if (atoi(operacion->cRequest) == cliente->idCliente) {
			if (strcmp(operacion->cFormato, "JSON") == 0) {
				clienteToJSON(*cliente, operacion->cResponse);
			}
			else {
				clienteToXML(*cliente, operacion->cResponse);
			}
			cliente_encontrado = 1;
		}
		if (ls_MoverCorriente(&ws->TClientes, LS_SIGUIENTE) == FALSE && cliente_encontrado == 0) {
			strcpy(operacion->cResponse, "El cliente no existe.\n");
			break;
		}
	} while (cliente_encontrado == 0);

	if (por_consola == 1) printf("%s", operacion->cResponse);

	free(cliente);

	if (cliente_encontrado == 0) return (1);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);

	return (0);
}

int getMaxIdClient(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	TElemCliente *cliente = malloc(sizeof(TElemCliente));
	char str[4];
	int max_id = 0;

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "getMaxIdClient") != 0) return (-1);

	getTime(ws, operacion->dOperacion, 0);

	ls_MoverCorriente(&ws->TClientes, LS_PRIMERO);
	do {
		ls_ElemCorriente(ws->TClientes, cliente);
	} while (ls_MoverCorriente(&ws->TClientes, LS_SIGUIENTE) == TRUE);
	sprintf(str, "%d", cliente->idCliente);
	if (strcmp(ws->TOperacion.cFormato, "JSON") == 0) {
		strcpy(operacion->cResponse, "'{\"ClientId\":\"");
		strcat(operacion->cResponse, str);
		strcat(operacion->cResponse, "\"}'");
	}
	else {
		strcpy(operacion->cResponse, "<ClientId>");
		strcat(operacion->cResponse, str);
		strcat(operacion->cResponse, "</ClientId>");
	}

	if (por_consola == 1) printf("%s", operacion->cResponse);

	max_id = cliente->idCliente;

	free(cliente);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);

	return (max_id);
}

int setMaxIdClient(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	TElemCliente *cliente = malloc(sizeof(TElemCliente));
	char *token;
	char linea[MAX_LINEA], linea_temp[MAX_LINEA];
	char str[4];
	char clave[50];
	char path_clientes[50], path_clientes_nuevo[53];

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "setMaxIdClient") != 0) return (-1);

	strcpy(operacion->cRequest, ws->TOperacion.cRequest);

	getTime(ws, operacion->dOperacion, 0);

	ls_MoverCorriente(&ws->TClientes, LS_PRIMERO);
	do {
		ls_ElemCorriente(ws->TClientes, cliente);
	} while (ls_MoverCorriente(&ws->TClientes, LS_SIGUIENTE) == TRUE);

	int id_cliente_anterior = cliente->idCliente;
	cliente->idCliente++;

	sprintf(str, "%d", cliente->idCliente);
	if (strcmp(ws->TOperacion.cFormato, "JSON") == 0) {
		strcpy(operacion->cResponse, "'{\"ClientId\":\"");
		strcat(operacion->cResponse, str);
		strcat(operacion->cResponse, "\"}'");
	}
	else {
		strcpy(operacion->cResponse, "<ClientId>");
		strcat(operacion->cResponse, str);
		strcat(operacion->cResponse, "</ClientId>");
	}

	FILE *arch_config = fopen(path_config,"r");

	for (unsigned int i = 0; i < 3; i++) {
		fgets(clave, sizeof(clave), arch_config);
		token = strtok(clave, "=");
		if (strcmp(token, "pathOperaciones") == 0) continue;
		else if (strcmp(token, "pathClientes") == 0) {
			token = strtok(NULL, "=");
			if (NULL != token) {
				strcpy(path_clientes, token);
				path_clientes[strlen(path_clientes) - 2] = '\0';
				strcpy(path_clientes_nuevo, path_clientes);
				strcat(path_clientes_nuevo, ".tmp");
			}
		}
		else if (strcmp(token, "pathLog") == 0) {
			continue;
		}
	}

	fclose(arch_config);

	FILE *arch_original = fopen(path_clientes, "r");
	FILE *arch_nuevo = fopen(path_clientes_nuevo, "w");
	while (fgets(linea, MAX_LINEA, arch_original)) {
		strcpy(linea_temp, linea);
		token = strtok(linea, ";");
		int id_cliente = atoi(token);
		if (id_cliente != id_cliente_anterior) {
			fputs(linea_temp, arch_nuevo);
		}
		else {
			fputs(str, arch_nuevo);
			fputs(";", arch_nuevo);
			fputs(cliente->Nombre, arch_nuevo);
			fputs(";", arch_nuevo);
			fputs(cliente->Apellido, arch_nuevo);
			fputs(";", arch_nuevo);
			fputs(cliente->Telefono, arch_nuevo);
			fputs(";", arch_nuevo);
			fputs(cliente->mail, arch_nuevo);
			fputs(";", arch_nuevo);
			fputs(operacion->dOperacion, arch_nuevo);
			fputs("\n", arch_nuevo);
		}
	}
	fclose(arch_nuevo);
	fclose(arch_original);
	remove(path_clientes);
	rename(path_clientes_nuevo, path_clientes);

	if (por_consola == 1) printf("%s", operacion->cResponse);

	free(cliente);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);

	return (0);
}

int setClientById(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "setClientById") != 0) return (-1);

	strcpy(operacion->cRequest, ws->TOperacion.cRequest);

	TElemCliente *cliente = malloc(sizeof(TElemCliente));
	if (!cliente) return (-1);
	FILE *arch_original;
	char linea[MAX_LINEA], linea_temp[MAX_LINEA];
	char str[4];
	char clave[50];
	char *token;

	char path_clientes[50], path_clientes_nuevo[53];

	FILE *arch_config = fopen(path_config,"r");

	for (unsigned int i = 0; i < 3; i++) {
		fgets(clave, sizeof(clave), arch_config);
		token = strtok(clave, "=");
		if (strcmp(token, "pathOperaciones") == 0) continue;
		else if (strcmp(token, "pathClientes") == 0) {
			token = strtok(NULL, "=");
			if (NULL != token) {
				strcpy(path_clientes, token);
				path_clientes[strlen(path_clientes) - 2] = '\0';
				strcpy(path_clientes_nuevo, path_clientes);
				strcat(path_clientes_nuevo, ".tmp");
			}
		}
		else if (strcmp(token, "pathLog") == 0) {
			continue;
		}
	}

	fclose(arch_config);

	if (strcmp(ws->TOperacion.cFormato, "JSON") == 0) {
		parseaClienteJSON(cliente, ws->TOperacion.cRequest);
	}
	else {
		parseaClienteXML(cliente, ws->TOperacion.cRequest);
	}

	getTime(ws, operacion->dOperacion, 0);
	if (getClientById(ws, 0, cliente->idCliente) == 1) {
		cliente->idCliente = getMaxIdClient(ws, 0) + 1;
		arch_original = fopen(path_clientes, "a");
		sprintf(str, "%d", cliente->idCliente);
		fputs(str, arch_original);
		fputs(";", arch_original);
		fputs(cliente->Nombre, arch_original);
		fputs(";", arch_original);
		fputs(cliente->Apellido, arch_original);
		fputs(";", arch_original);
		fputs(cliente->Telefono, arch_original);
		fputs(";", arch_original);
		fputs(cliente->mail, arch_original);
		fputs(";", arch_original);
		fputs(operacion->dOperacion, arch_original);
		fputs("\n", arch_original);
		fclose(arch_original);
	}
	else {
		arch_original = fopen(path_clientes, "r");
		FILE *arch_nuevo = fopen(path_clientes_nuevo, "w");
		while (fgets(linea, MAX_LINEA, arch_original)) {
			strcpy(linea_temp, linea);
			token = strtok(linea, ";");
			int id_cliente = atoi(token);
			if (id_cliente != cliente->idCliente) {
				fputs(linea_temp, arch_nuevo);
			}
			else {
				sprintf(str, "%d", cliente->idCliente);
				fputs(str, arch_nuevo);
				fputs(";", arch_nuevo);
				fputs(cliente->Nombre, arch_nuevo);
				fputs(";", arch_nuevo);
				fputs(cliente->Apellido, arch_nuevo);
				fputs(";", arch_nuevo);
				fputs(cliente->Telefono, arch_nuevo);
				fputs(";", arch_nuevo);
				fputs(cliente->mail, arch_nuevo);
				fputs(";", arch_nuevo);
				fputs(operacion->dOperacion, arch_nuevo);
				fputs("\n", arch_nuevo);
			}
		}
		fclose(arch_nuevo);
		fclose(arch_original);
		remove(path_clientes);
		rename(path_clientes_nuevo, path_clientes);
	}

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);

	free(cliente);

	return (0);
}

int getAllClients(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "getAllClients") != 0) return (-1);

	char str[4];
	TElemCliente *cliente = malloc(sizeof(TElemCliente));

	getTime(ws, operacion->dOperacion, 0);

	if (strcmp(ws->TOperacion.cFormato, "JSON") == 0) {
		strcpy(operacion->cResponse, "'\"clientes\" :[");
		ls_MoverCorriente(&ws->TClientes, LS_PRIMERO);
		do {
			ls_ElemCorriente(ws->TClientes, cliente);
			sprintf(str, "%d", cliente->idCliente);
			strcat(operacion->cResponse, "{\"id\":\"");
			strcat(operacion->cResponse, str);
			strcat(operacion->cResponse, ",\"Nombre\":");
			strcat(operacion->cResponse, cliente->Nombre);
			strcat(operacion->cResponse, ",\"Apellido\":");
			strcat(operacion->cResponse, cliente->Apellido);
			strcat(operacion->cResponse, ",\"Telefono\":");
			strcat(operacion->cResponse, cliente->Telefono);
			strcat(operacion->cResponse, ",\"Mail\":");
			strcat(operacion->cResponse, cliente->mail);
			strcat(operacion->cResponse, ",\"Time\":");
			strcat(operacion->cResponse, operacion->dOperacion);
			strcat(operacion->cResponse, "\"}");
		} while (ls_MoverCorriente(&ws->TClientes, LS_SIGUIENTE) == TRUE);
	}
	else {
		strcpy(operacion->cResponse, "'<?xml version=\"1.0\" encoding=\"UTF-8\"?><Clientes>");
		ls_MoverCorriente(&ws->TClientes, LS_PRIMERO);
		do {
			ls_ElemCorriente(ws->TClientes, cliente);
			sprintf(str, "%d", cliente->idCliente);
			strcat(operacion->cResponse, "<Cliente><id>");
			strcat(operacion->cResponse, str);
			strcat(operacion->cResponse, "</id><Nombre>");
			strcat(operacion->cResponse, cliente->Nombre);
			strcat(operacion->cResponse, "</Nombre><Apellido>");
			strcat(operacion->cResponse, cliente->Apellido);
			strcat(operacion->cResponse, "</Apellido><Telefono>");
			strcat(operacion->cResponse, cliente->Telefono);
			strcat(operacion->cResponse, "</Telefono><mail>");
			strcat(operacion->cResponse, cliente->mail);
			strcat(operacion->cResponse, "</mail><Time>");
			strcat(operacion->cResponse, operacion->dOperacion);
			strcat(operacion->cResponse, "</Time></Cliente>");
		} while (ls_MoverCorriente(&ws->TClientes, LS_SIGUIENTE) == TRUE);
		strcat(operacion->cResponse, "</Clientes>'");
	}

	if (por_consola == 1) printf("%s", operacion->cResponse);

	free(cliente);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);

	return (0);
}

int getAllOperations(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	char *operacion_actual = malloc(sizeof(TDAWSOperacion));
	if (!operacion_actual) return (-1);

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "getAllOperations") != 0) return (-1);

	getTime(ws, operacion->dOperacion, 0);

	ls_MoverCorriente(&ws->LOperaciones, LS_PRIMERO);
	if (strcmp(ws->TOperacion.cFormato, "JSON") == 0) {
		strcpy(operacion->cResponse, "'\"operaciones\" :[");
		ls_MoverCorriente(&ws->LOperaciones, LS_PRIMERO);
		do {
			ls_ElemCorriente(ws->LOperaciones, operacion_actual);
			strcat(operacion->cResponse, "{\"Operacion\":\"");
			strcat(operacion->cResponse, operacion_actual);
			strcat(operacion->cResponse, "\"}");
		} while (ls_MoverCorriente(&ws->LOperaciones, LS_SIGUIENTE) == TRUE);
		strcat(operacion->cResponse, "}");
	}
	else {
		strcpy(operacion->cResponse, "'<?xml version=\"1.0\" encoding=\"UTF-8\"?><Operaciones>");
		ls_MoverCorriente(&ws->LOperaciones, LS_PRIMERO);
		do {
			ls_ElemCorriente(ws->LOperaciones, operacion_actual);
			strcat(operacion->cResponse, "<Operacion>");
			strcat(operacion->cResponse, operacion_actual);
			strcat(operacion->cResponse, "</Operacion>");
		} while (ls_MoverCorriente(&ws->LOperaciones, LS_SIGUIENTE) == TRUE);
		strcat(operacion->cResponse, "</Operaciones>'");
	}

	if (por_consola == 1) printf("%s", operacion->cResponse);

	free(operacion_actual);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);

	return (0);
}

int validateOperation(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "validateOperation") != 0) return (-1);

	strcpy(operacion->cRequest, ws->TOperacion.cOperacion);

	getTime(ws, operacion->dOperacion, 0);

	char operacion_valida = 1;
	char nombre_operacion[20];
	char validez[6];
	strcpy(validez, "false");

	ls_ElemCorriente(ws->LOperaciones, nombre_operacion);
	while (operacion_valida == 1) {
		if (strcmp(ws->TOperacion.cOperacion, nombre_operacion) == 0) {
			operacion_valida = 0;
			strcpy(validez, "true");
		}
		else
			if (ls_MoverCorriente(&ws->LOperaciones, LS_SIGUIENTE) == TRUE)
				ls_ElemCorriente(ws->LOperaciones, nombre_operacion);
			else
				break;
		}

	if (strcmp(ws->TOperacion.cFormato, "JSON") == 0) {
		strcpy(operacion->cResponse, "'{\"valid\":\"");
		strcat(operacion->cResponse, validez);
		strcat(operacion->cResponse, "\"}'\n");
	}
	else {
		strcpy(operacion->cResponse, "<valid>");
		strcat(operacion->cResponse, validez);
		strcat(operacion->cResponse, "</valid>\n");
	}

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);
	return (operacion_valida);
}
