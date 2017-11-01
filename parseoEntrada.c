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
	//int largo;

	/* COPIA ID */
	inicio = strstr(lineaXML, "<id>") + sizeof(char) * 5;
	token = strtok(inicio, "<");
	//largo = ((strstr(inicio, "</id>") - inicio) / sizeof(char));
	strcpy(cadenaAuxiliar, token);
	clienteNuevo->idCliente = atoi(cadenaAuxiliar);

	/* COPIA NOMBRE */
	inicio = strstr(lineaXML, "<Nombre>") + sizeof(char) * 9;
	token = strtok(inicio, "<");
	//largo = ((strstr(inicio, "</Nombre>") - inicio) / sizeof(char));
	strcpy(clienteNuevo->Nombre, token);

	/* COPIA APELLIDO */
	inicio = strstr(lineaXML, "<Apellido>") + sizeof(char) * 10;
	token = strtok(inicio, "<");
	//largo = ((strstr(inicio, "</Apellido>") - inicio) / sizeof(char));
	strcpy(clienteNuevo->Apellido, token);

	/* COPIA TELEFONO */
	inicio = strstr(lineaXML, "<Telefono>") + sizeof(char) * 11;
	token = strtok(inicio, "<");
	//largo = ((strstr(inicio, "</Telefono>") - inicio) / sizeof(char));
	strcpy(clienteNuevo->Telefono, token);

	/* COPIA MAIL */
	inicio = strstr(lineaXML, "<Mail>") + sizeof(char) * 7;
	token = strtok(inicio, "<");
	//largo = ((strstr(inicio, "</Mail>") - inicio) / sizeof(char));
	strcpy(clienteNuevo->mail, token);

	/* COPIA FECHA */
	inicio = strstr(lineaXML, "<Time>") + sizeof(char) * 7;
	token = strtok(inicio, "<");
	//largo = ((strstr(inicio, "</Time>") - inicio) / sizeof(char));
	strcpy(clienteNuevo->fecha, token);

}


void parseaClienteJSON(TElemCliente *clienteNuevo, char *lineaJSON) {
	char *inicio, *token;
	char cadenaAuxiliar[4];
	//int largo;

	/* COPIA ID */
	inicio = strstr(lineaJSON, "\"id\": \"") + sizeof(char) * 8;
	token = strtok(inicio, "\"");
	//largo = ((strstr(inicio, "\"") - inicio) / sizeof(char));
	strcpy(cadenaAuxiliar, token);
	clienteNuevo->idCliente = atoi(cadenaAuxiliar);

	/* COPIA NOMBRE */
	inicio = strstr(lineaJSON, "\"Nombre\": \"") + sizeof(char) * 12;
	token = strtok(inicio, "\"");
	//largo = ((strstr(inicio, "\"") - inicio) / sizeof(char));
	strcpy(clienteNuevo->Nombre, token);

	/* COPIA APELLIDO */
	inicio = strstr(lineaJSON, "\"Apellido\": \"") + sizeof(char) * 14;
	token = strtok(inicio, "\"");
	//largo = ((strstr(inicio, "\"") - inicio) / sizeof(char));
	strcpy(clienteNuevo->Apellido, token);

	/* COPIA TELEFONO */
	inicio = strstr(lineaJSON, "\"Telefono\": \"") + sizeof(char) * 14;
	token = strtok(inicio, "\"");
	//largo = ((strstr(inicio, "\"") - inicio) / sizeof(char));
	strcpy(clienteNuevo->Telefono, token);

	/* COPIA MAIL */
	inicio = strstr(lineaJSON, "\"Mail\": \"") + sizeof(char) * 10;
	token = strtok(inicio, "\"");
	//largo = ((strstr(inicio, "\"") - inicio) / sizeof(char));
	strcpy(clienteNuevo->mail, token);

	/* COPIA FECHA */
	inicio = strstr(lineaJSON, "\"Time\": \"") + sizeof(char) * 10;
	token = strtok(inicio, "\"");
	//largo = ((strstr(inicio, "\"") - inicio) / sizeof(char));
	strcpy(clienteNuevo->fecha, token);
}
