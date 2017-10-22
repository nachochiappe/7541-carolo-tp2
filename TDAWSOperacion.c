/*
 * TDAWSOperacion.c
 *
 *  Created on: 16 Oct 2017
 *      Author: Yoel
 */

#include <stdio.h>
#include <string.h>

#include "TDAWSOperacion.h"

void parserXML(TDAWS *ws) {

}

void parserJSON(TDAWS *ws) {

}

void getTime(TDAWS *ws, char por_consola) {

}

void getMaxIdClient(TDAWS *ws, char por_consola) {

}

void setMaxIdClient(TDAWS *ws, char por_consola) {

}

void getClientById(TDAWS *ws, char por_consola) {

}

void setClientById(TDAWS *ws, char por_consola) {

}

void getAllClients(TDAWS *ws, char por_consola) {

}

void getAllOperations(TDAWS *ws, char por_consola) {

}

int validateOperation(TDAWS *ws, char por_consola) {
	char operacion_valida = 1;
	char nombre_operacion[20];

	if (por_consola == 1) {
		if (strcmp(ws->TOperacion.cFormato, "JSON") == 0)
			printf("'{\"valid\":\"");
		else
			printf("<valid>");
	}

	ls_ElemCorriente(ws->LOperaciones, nombre_operacion);
	while (operacion_valida == 1) {
		if (strcmp(ws->TOperacion.dOperacion, nombre_operacion) == 0) {
			operacion_valida = 0;
		}
		else
			if (ls_MoverCorriente(&ws->LOperaciones, LS_SIGUIENTE) != 0)
				break;
		}
	if (por_consola == 1) {
		if (operacion_valida == 0)
			printf("true");
		else
			printf("false");
		if (strcmp(ws->TOperacion.cFormato, "JSON") == 0)
			printf("\"}'\n");
		else
			printf("</valid>\n");
	}
	return operacion_valida;
}
