/*
 * parserXML.c
 *
 *  Created on: 28 oct. 2017
 *      Author: fernando
 */

#include "parseoEntrada.h"

void parseaClienteXML(TElemCliente *clienteNuevo, char *lineaXML) {
	char *inicio, *cadenaAuxiliar;
	int largo;

	/* COPIA ID */
	inicio = strstr(lineaXML, "<id>") + sizeof(char) * 5;
	largo = ((strstr(inicio, "</id>") - inicio) / sizeof(char));
	strcpy(cadenaAuxiliar, inicio, largo);
	clienteNuevo->idCliente = atoi(cadenaAuxiliar);

	/* COPIA NOMBRE */
	inicio = strstr(lineaXML, "<Nombre>") + sizeof(char) * 9;
	largo = ((strstr(inicio, "</Nombre>") - inicio) / sizeof(char));
	strcpy(clienteNuevo->Nombre, inicio, largo);

	/* COPIA APELLIDO */
	inicio = strstr(lineaXML, "<Apellido>") + sizeof(char) * 10;
	largo = ((strstr(inicio, "</Apellido>") - inicio) / sizeof(char));
	strcpy(clienteNuevo->Apellido, inicio, largo);

	/* COPIA TELEFONO */
	inicio = strstr(lineaXML, "<Telefono>") + sizeof(char) * 11;
	largo = ((strstr(inicio, "</Telefono>") - inicio) / sizeof(char));
	strcpy(clienteNuevo->Telefono, inicio, largo);

	/* COPIA MAIL */
	inicio = strstr(lineaXML, "<Mail>") + sizeof(char) * 7;
	largo = ((strstr(inicio, "</Mail>") - inicio) / sizeof(char));
	strcpy(clienteNuevo->mail, inicio, largo);

	/* COPIA FECHA */
	inicio = strstr(lineaXML, "<Time>") + sizeof(char) * 7;
	largo = ((strstr(inicio, "</Time>") - inicio) / sizeof(char));
	strcpy(clienteNuevo->fecha, inicio, largo);

}


void parseaClienteJSON(TElemCliente *clienteNuevo, char *lineaJSON) {
	char *inicio, *cadenaAuxiliar;
	int largo;

	/* COPIA ID */
	inicio = strstr(lineaJSON, "\"id\": \"") + sizeof(char) * 8;
	largo = ((strstr(inicio, "\"") - inicio) / sizeof(char));
	strcpy(cadenaAuxiliar, inicio, largo);
	clienteNuevo->idCliente = atoi(cadenaAuxiliar);

	/* COPIA NOMBRE */
	inicio = strstr(lineaJSON, "\"Nombre\": \"") + sizeof(char) * 12;
	largo = ((strstr(inicio, "\"") - inicio) / sizeof(char));
	strcpy(clienteNuevo->Nombre, inicio, largo);

	/* COPIA APELLIDO */
	inicio = strstr(lineaJSON, "\"Apellido\": \"") + sizeof(char) * 14;
	largo = ((strstr(inicio, "\"") - inicio) / sizeof(char));
	strcpy(clienteNuevo->Apellido, inicio, largo);

	/* COPIA TELEFONO */
	inicio = strstr(lineaJSON, "\"Telefono\": \"") + sizeof(char) * 14;
	largo = ((strstr(inicio, "\"") - inicio) / sizeof(char));
	strcpy(clienteNuevo->Telefono, inicio, largo);

	/* COPIA MAIL */
	inicio = strstr(lineaJSON, "\"Mail\": \"") + sizeof(char) * 10;
	largo = ((strstr(inicio, "\"") - inicio) / sizeof(char));
	strcpy(clienteNuevo->mail, inicio, largo);

	/* COPIA FECHA */
	inicio = strstr(lineaJSON, "\"Time\": \"") + sizeof(char) * 10;
	largo = ((strstr(inicio, "\"") - inicio) / sizeof(char));
	strcpy(clienteNuevo->fecha, inicio, largo);
}
