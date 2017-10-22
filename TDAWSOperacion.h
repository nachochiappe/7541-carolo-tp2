/*
 * TDAWSOperacion.h
 *
 *  Created on: 16 Oct 2017
 *      Author: Yoel
 */

#ifndef TDAWSOPERACION_H_
#define TDAWSOPERACION_H_

#include "structs.h"

void parserXML(TDAWS *ws);

void parserJSON(TDAWS *ws);

void getTime(TDAWS *ws, char por_consola);

void getMaxIdClient(TDAWS *ws, char por_consola);

void setMaxIdClient(TDAWS *ws, char por_consola);

void getClientById(TDAWS *ws, char por_consola);

void setClientById(TDAWS *ws, char por_consola);

void getAllClients(TDAWS *ws, char por_consola);

void getAllOperations(TDAWS *ws, char por_consola);

void validateOperation(TDAWS *ws, char por_consola);

#endif /* TDAWSOPERACION_H_ */
