/*
 * TDAWSOperacion.h
 *
 *  Created on: 16 Oct 2017
 *      Author: Yoel
 */

#ifndef TDAWSOPERACION_H_
#define TDAWSOPERACION_H_

typedef struct TDAWSOperacion
{
	char * cRequest; /* Request al servicio */
	char * cResponse; /* Response del servicio*/
	char * cOperacion; /* Nombre de la operaci�n */
	char * dOperacion; /* Fecha de ejecuci�n*/
	char * cFormato; /* Formato de intercambio XML/JSON*/
} TDAWSOperacion;

#endif /* TDAWSOPERACION_H_ */

void parserXML(TDAWS *ws);

void parserJSON(TDAWS *ws);

void getTime(TDAWS *ws);

void getClientById(TDAWS *ws);

void getMaxIdClient(TDAWS *ws);

void setMaxIdClient(TDAWS *ws);

void getAllClients(TDAWS *ws);

void getAllOperations(TDAWS *ws);

void validateOperation(TDAWS *ws);
