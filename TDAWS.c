/*
 * TDAWS.C
 *
 *  Created on: 16 Oct 2017
 *      Author: Yoel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cola.h"
#include "lista.h"
#include "pila.h"
#include "TDAWS.h"
#include "TDAWSOperacion.h"

#define path_config "SERVERTP2GRUPAL.conf"

int TDAWS_Crear(TDAWS *ws, char **cmd) {

	// OBTENER VALORES DE ARCHIVO DE CONFIGURACION

	char str[50];
	char *token;

	char path_operaciones[50];
	char path_clientes[50];

	FILE *arch_config = fopen(path_config,"r");

	for (unsigned int i = 0; i < 3; i++) {
		fgets(str, sizeof(str), arch_config);
		token = strtok(str, "=");
		if (strcmp(token, "pathOperaciones") == 0) {
			token = strtok(NULL, "=");
			if (NULL != token) {
				strcpy(path_operaciones, token);
				path_operaciones[strlen(path_operaciones) - 2] = '\0';
			}

		}
		else if (strcmp(token, "pathClientes") == 0) {
			token = strtok(NULL, "=");
			if (NULL != token) {
				strcpy(path_clientes, token);
				path_clientes[strlen(path_clientes) - 2] = '\0';
			}
		}
		else if (strcmp(token, "pathLog") == 0) {
			continue;
		}
		else {
			printf("El archivo de configuración tiene valores incorrectos.\n");
			return (-1);
		}
	}

	fclose(arch_config);

	// LISTA DE OPERACIONES DISPONIBLES

	ls_Crear(&ws->LOperaciones, 20);
	char nombre_operacion[20];
	FILE *arch_operaciones = fopen(path_operaciones,"r");
	while (fgets(nombre_operacion, sizeof(nombre_operacion), arch_operaciones) != NULL)
		ls_Insertar(&ws->LOperaciones, LS_SIGUIENTE, nombre_operacion);
	fclose(arch_operaciones);

	// LISTA DE TDAClientes

	ls_Crear(&ws->TClientes, sizeof(TElemCliente));
	TElemCliente *cliente = (TElemCliente*) malloc(sizeof(TElemCliente));
	if (!cliente) return (-1);
	char linea_cliente[255];
	FILE *arch_clientes = fopen(path_clientes,"r");
	while (fgets(linea_cliente, sizeof(TElemCliente), arch_clientes) != NULL) {
		token = strtok(linea_cliente, ";");
		cliente->idCliente = atoi(token);
		token = strtok(NULL, ";");
		strcpy(cliente->Nombre, token);
		token = strtok(NULL, ";");
		strcpy(cliente->Apellido, token);
		token = strtok(NULL, ";");
		strcpy(cliente->Telefono, token);
		token = strtok(NULL, ";");
		strcpy(cliente->mail, token);
		token = strtok(NULL, ";");
		strcpy(cliente->fecha, token);
		ls_Insertar(&ws->TClientes, LS_SIGUIENTE, cliente);
	}
	fclose(arch_clientes);

	// COLA CON LAS OPERACIONES EJECUTADAS

	C_Crear(&ws->CEjecucion, sizeof(TDAWSOperacion));
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	if (inicializarOperacion(operacion) != 0) return (-1);

	char tipo_op = 0; // 0 = POST; 1 = GET
	enum formato tipo_formato;
	unsigned char i = 1;
	if (strcmp(cmd[i], "-X") == 0) {
		// Verifico si es GET o POST
		i++;
		if (strcmp(cmd[i], "GET") == 0)
			tipo_op++;
		else if (strcmp(cmd[i], "POST") != 0) return (-1);

		i++;
		if (strcmp(cmd[i], "-H") == 0) {
			// Verifico si es JSON o XML
			i++;
			if (tipo_op == 0) {
				if (strcmp(cmd[i], "Content-Type:application/json") == 0)
					tipo_formato = JSON;
				else if (strcmp(cmd[i], "Content-Type:application/xml") == 0)
					tipo_formato = XML;
				else return (-1);
			}
			else {
				if (strcmp(cmd[i], "Accept:application/json") == 0)
					tipo_formato = JSON;
				else if (strcmp(cmd[i], "Accept:application/xml") == 0)
					tipo_formato = XML;
				else return (-1);
			}

			// Obtengo nombre de operación
			i++;
			char *URL = cmd[i];
			token = strtok(URL, "/");
			for (int j = 0; j < 2; j++) {
				token = strtok(NULL, "/");
			}
			if (strcmp(token, "getClientById") == 0)
				token = strtok(NULL, "/");
			else if (strcmp(token, "setClientById") == 0) {
				i++;
				if (strcmp(cmd[i], "-d") == 0) {
					i++;
					operacion->cRequest = cmd[i];
				}
				else return (-1);
			}

			// Completo parámetros operación
			//operacion->cResponse = NULL;
			//operacion->cOperacion = malloc(strlen(token) + 1);
			strcpy(operacion->cOperacion, token);
			//operacion->dOperacion = NULL;
			if (tipo_formato == JSON) {
				//operacion->cFormato = malloc(strlen("JSON") + 1);
				strcpy(operacion->cFormato, "JSON");
			}
			else {
				//operacion->cFormato = malloc(sizeof("XML") + 1);
				strcpy(operacion->cFormato, "XML");
			}
			ws->TOperacion = (*operacion);
		}
	}
	else return (-1);

	return (0);
}

int TDAWS_OperacionValida(TDAWS *ws) {
	return (validateOperation(ws, 0));
}

int TDAWS_Consumir(TDAWS *ws) {
	if (strcmp(ws->TOperacion.cOperacion, "getTime") == 0) {
		getTime(ws, ws->TOperacion.cOperacion, 1);
	}
	else if (strcmp(ws->TOperacion.cOperacion, "getMaxIdClient") == 0) {
		getMaxIdClient(ws, 1);
	}
	else if (strcmp(ws->TOperacion.cOperacion, "setMaxIdClient") == 0) {
		setMaxIdClient(ws, 1);
	}
	else if (strcmp(ws->TOperacion.cOperacion, "getClientById") == 0) {
		getClientById(ws, 1);
	}
	else if (strcmp(ws->TOperacion.cOperacion, "setClientById") == 0) {
		setClientById(ws, 1);
	}
	else if (strcmp(ws->TOperacion.cOperacion, "getAllClients") == 0) {
		getAllClients(ws, 1);
	}
	else if (strcmp(ws->TOperacion.cOperacion, "getAllOperations") == 0) {
		getAllOperations(ws, 1);
	}
	else if (strcmp(ws->TOperacion.cOperacion, "validateOperation") == 0) {
		validateOperation(ws, 1);
	}
	return (0);
}

int TDAWS_Destruir(TDAWS *ws) {
	char str[50];
	char *token;
	char path_log[50];

	FILE *arch_config = fopen(path_config,"r");

	for (unsigned int i = 0; i < 3; i++) {
		fgets(str, sizeof(str), arch_config);
		token = strtok(str, "=");
		if (strcmp(token, "pathLog") == 0) {
			token = strtok(NULL, "=");
			if (NULL != token) {
				strcpy(path_log, token);
				path_log[strlen(path_log) - 2] = '\0';
			}
		}
		else {
			printf("No existe variable 'pathLog' en archivo de configuracion.\n");
			return (-1);
		}
	}

	fclose(arch_config);

	FILE *arch_log = fopen(path_log,"r+");

	while (C_Vacia(ws->CEjecucion) == 0) {
		TDAWSOperacion* operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
		if (!operacion) return (-1);
		C_Sacar(&ws->CEjecucion, operacion);
		// La operación getTime no se debe loguear
		if (strcmp(operacion->cOperacion, "getTime") != 0) {
			fputs(operacion->dOperacion, arch_log);
			fputs(";", arch_log);
			fputs(operacion->cOperacion, arch_log);
			fputs(";", arch_log);
			fputs(operacion->cRequest, arch_log);
			fputs(";", arch_log);
			fputs(operacion->cResponse, arch_log);
			fputs("\n", arch_log);
		}
		free(operacion->cFormato);
		free(operacion->cOperacion);
		free(operacion->cRequest);
		free(operacion->cResponse);
		free(operacion->dOperacion);
		free(operacion);
	}
	C_Vaciar(&ws->CEjecucion);

	fclose(arch_log);

	ls_Vaciar(&ws->TClientes);

	free(ws);

	return (0);
}
