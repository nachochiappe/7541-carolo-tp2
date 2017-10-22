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

void getTime(TDAWS *ws);

void getClientById(TDAWS *ws);

void getMaxIdClient(TDAWS *ws);

void setMaxIdClient(TDAWS *ws);

void getAllClients(TDAWS *ws);

void getAllOperations(TDAWS *ws);

void validateOperation(TDAWS *ws);

#endif /* TDAWSOPERACION_H_ */
