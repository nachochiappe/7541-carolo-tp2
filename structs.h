/*
 * structs.h
 *
 *  Created on: 22 oct. 2017
 *      Author: nacho
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include "cola.h"
#include "lista.h"

enum formato {JSON = 1, XML = 0};

typedef struct TDAWSOperacion {
	char * cRequest; /* Request al servicio */
	char * cResponse; /* Response del servicio*/
	char * cOperacion; /* Nombre de la operación */
	char * dOperacion; /* Fecha de ejecución*/
	char * cFormato; /* Formato de intercambio XML/JSON*/
} TDAWSOperacion;

typedef struct TDAWS {
	TDAWSOperacion TOperacion; /*Operación actual que se consume*/
	TLista LOperaciones; /* Lista con las operaciones disponibles */
	TLista TClientes; /*Lista de TDAClientes con cantidad*/
	TCola CEjecucion; /*Cola con las operaciones ejecutadas*/
} TDAWS;

typedef struct TElemCliente {
	int idCliente;
	char Nombre[20];
	char Apellido[20];
	char Telefono[20];
	char mail[20];
	char fecha[20];
} TElemCliente;

#endif /* STRUCTS_H_ */
