/*
 * parserXML.c
 *
 *  Created on: 28 oct. 2017
 *      Author: fernando
 */

#include "parseoEntrada.h"
#include <string.h>
#include <stdlib.h>

void parseaClienteXML(TElemCliente *clienteNuevo, char *lineaXML) {
	char *inicio, *token;
	char cadenaAuxiliar[4];
	char *cadenaTemp = malloc(strlen(lineaXML) + 1);
	if (!cadenaTemp) return;

	/* COPIA ID */
	strcpy(cadenaTemp, lineaXML);
	inicio = strstr(cadenaTemp, "<id>") + 4;
	token = strtok(inicio, "<");
	strcpy(cadenaAuxiliar, token);
	clienteNuevo->idCliente = atoi(cadenaAuxiliar);

	/* COPIA NOMBRE */
	strcpy(cadenaTemp, lineaXML);
	inicio = strstr(cadenaTemp, "<Nombre>") + 8;
	token = strtok(inicio, "<");
	strcpy(clienteNuevo->Nombre, token);

	/* COPIA APELLIDO */
	strcpy(cadenaTemp, lineaXML);
	inicio = strstr(cadenaTemp, "<Apellido>") + 10;
	token = strtok(inicio, "<");
	strcpy(clienteNuevo->Apellido, token);

	/* COPIA TELEFONO */
	strcpy(cadenaTemp, lineaXML);
	inicio = strstr(cadenaTemp, "<Telefono>") + 10;
	token = strtok(inicio, "<");
	strcpy(clienteNuevo->Telefono, token);

	/* COPIA MAIL */
	strcpy(cadenaTemp, lineaXML);
	inicio = strstr(cadenaTemp, "<Mail>") + 6;
	token = strtok(inicio, "<");
	strcpy(clienteNuevo->mail, token);

	/* COPIA FECHA */
	strcpy(cadenaTemp, lineaXML);
	inicio = strstr(cadenaTemp, "<Time>") + 6;
	token = strtok(inicio, "<");
	strcpy(clienteNuevo->fecha, token);

	free(cadenaTemp);
}


void parseaClienteJSON(TElemCliente *clienteNuevo, char *lineaJSON) {
	char *token;
	char cadenaAuxiliar[4];
	char *inicio;
	char *cadenaTemp = malloc(strlen(lineaJSON) + 1);
	if (!cadenaTemp) return;

	/* COPIA ID */
	strcpy(cadenaTemp, lineaJSON);
	inicio = strstr(cadenaTemp, "id:") + 3;
	token = strtok(inicio, ",");
	strcpy(cadenaAuxiliar, token);
	clienteNuevo->idCliente = atoi(cadenaAuxiliar);

	/* COPIA NOMBRE */
	strcpy(cadenaTemp, lineaJSON);
	inicio = strstr(cadenaTemp, "Nombre:") + 7;
	token = strtok(inicio, ",");
	strcpy(clienteNuevo->Nombre, token);

	/* COPIA APELLIDO */
	strcpy(cadenaTemp, lineaJSON);
	inicio = strstr(cadenaTemp, "Apellido:") + 9;
	token = strtok(inicio, ",");
	strcpy(clienteNuevo->Apellido, token);

	/* COPIA TELEFONO */
	strcpy(cadenaTemp, lineaJSON);
	inicio = strstr(cadenaTemp, "Telefono:") + 9;
	token = strtok(inicio, ",");
	strcpy(clienteNuevo->Telefono, token);

	/* COPIA MAIL */
	strcpy(cadenaTemp, lineaJSON);
	inicio = strstr(cadenaTemp, "Mail:") + 5;
	token = strtok(inicio, ",");
	strcpy(clienteNuevo->mail, token);

	/* COPIA FECHA */
	strcpy(cadenaTemp, lineaJSON);
	inicio = strstr(cadenaTemp, "Time:") + 5;
	token = strtok(inicio, "}");
	strcpy(clienteNuevo->fecha, token);

	free(cadenaTemp);
}
