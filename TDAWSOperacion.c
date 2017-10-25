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

void parserXML(TDAWS *ws) {

}

void parserJSON(TDAWS *ws) {

}

int getTime(TDAWS *ws, char *fecha, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
		if (!operacion) return (-1);

	time_t tiempo;
	time(&tiempo);
	fecha = ctime(&tiempo);

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

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &ws->TOperacion) != 0) return (-1);

	return (0);
}

int getClientById(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	getTime(ws, operacion->dOperacion, 0);

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &ws->TOperacion) != 0) return (-1);

	return (0);
}

int getMaxIdClient(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	getTime(ws, operacion->dOperacion, 0);



	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &ws->TOperacion) != 0) return (-1);

	return (0);
}

int setMaxIdClient(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	getTime(ws, operacion->dOperacion, 0);

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &ws->TOperacion) != 0) return (-1);

	return (0);
}

int setClientById(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	int id_cliente = 0;

	getTime(ws, operacion->dOperacion, 0);
	if (getClientById(ws, 0) == 1)
		id_cliente = getMaxIdClient(ws, 0) + 1;

	//setClientById

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &ws->TOperacion) != 0) return (-1);

	return (0);
}

int getAllClients(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	getTime(ws, operacion->dOperacion, 0);

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &ws->TOperacion) != 0) return (-1);

	return (0);
}

int getAllOperations(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	getTime(ws, operacion->dOperacion, 0);

	if (por_consola == 1) printf("%s", operacion->cResponse);

	if (C_Agregar(&ws->CEjecucion, &ws->TOperacion) != 0) return (-1);

	return (0);
}

int validateOperation(TDAWS *ws, char por_consola) {
	TDAWSOperacion *operacion = (TDAWSOperacion*) malloc(sizeof(TDAWSOperacion));
	if (!operacion) return (-1);

	getTime(ws, operacion->dOperacion, 0);

	char operacion_valida = 1;
	char nombre_operacion[20];
	char validez[6];
	strcpy(validez, "false");

	ls_ElemCorriente(ws->LOperaciones, nombre_operacion);
	while (operacion_valida == 1) {
		if (strcmp(ws->TOperacion.dOperacion, nombre_operacion) == 0) {
			operacion_valida = 0;
			strcpy(validez, "true");
		}
		else
			if (ls_MoverCorriente(&ws->LOperaciones, LS_SIGUIENTE) != 0)
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

	if (C_Agregar(&ws->CEjecucion, &ws->TOperacion) != 0) return (-1);
	return (operacion_valida);
}
