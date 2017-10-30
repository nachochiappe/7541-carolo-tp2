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

int inicializarOperacion(TDAWSOperacion *operacion, char *formato, char *nombre) {

	operacion->cRequest = malloc(200);
	if (!operacion->cRequest) return (-1);

	operacion->cResponse = malloc(200);
	if (!operacion->cResponse) return (-1);

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

int getClientById(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	TElemCliente *cliente;

	char cliente_encontrado = 0;

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "getClientById") != 0) return (-1);

	getTime(ws, operacion->dOperacion, 0);

	ls_ModifCorriente(ws->TClientes, LS_PRIMERO);
	do {
		if (ls_MoverCorriente(ws->TClientes, LS_SIGUIENTE) == FALSE) {
			strcpy(operacion->cResponse, "El cliente no existe.\n");
			break;
		}
		ls_ElemCorriente(ws->TClientes, cliente);
		if (/*si el ID del cliente del parámetro es igual al del cliente actual de la lista*/) {
			// TAG Elemento XML: cliente
			strcpy(operacion->cResponse, "\n");
			cliente_encontrado = 1;
		}
	} while (cliente_encontrado == 0);

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);

	return (0);
}

int getMaxIdClient(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "getMaxIdClient") != 0) return (-1);

	getTime(ws, operacion->dOperacion, 0);

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);

	return (0);
}

int setMaxIdClient(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "setMaxIdClient") != 0) return (-1);

	getTime(ws, operacion->dOperacion, 0);

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);

	return (0);
}

int setClientById(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "setClientById") != 0) return (-1);

	int id_cliente = 0;

	getTime(ws, operacion->dOperacion, 0);
	if (getClientById(ws, 0) == 1)
		id_cliente = getMaxIdClient(ws, 0) + 1;

	//setClientById

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);

	return (0);
}

int getAllClients(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "getAllClients") != 0) return (-1);

	getTime(ws, operacion->dOperacion, 0);

	ls_ModifCorriente(ws->TClientes, LS_PRIMERO);
	// TAG Principal: clientes
	do {
		// TAG Elemento XML: cliente
	} while (ls_MoverCorriente(ws->TClientes, LS_SIGUIENTE) == TRUE);

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &operacion) != TRUE) return (-1);

	return (0);
}

int getAllOperations(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	if (inicializarOperacion(operacion, ws->TOperacion.cFormato, "getAllOperations") != 0) return (-1);

	getTime(ws, operacion->dOperacion, 0);

	ls_ModifCorriente(ws->LOperaciones, LS_PRIMERO);
	// TAG Principal: operaciones
	do {
		// TAG Elemento XML: operacion
	} while (ls_MoverCorriente(ws->LOperaciones, LS_SIGUIENTE) == TRUE);

	if (por_consola == 1) printf("%s", operacion->cResponse);

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
			if (ls_MoverCorriente(&ws->LOperaciones, LS_SIGUIENTE) == 0)
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
