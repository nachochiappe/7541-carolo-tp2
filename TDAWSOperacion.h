/*
 * TDAWSOperacion.h
 *
 *  Created on: 16 Oct 2017
 *      Author: Yoel
 */

#ifndef TDAWSOPERACION_H_
#define TDAWSOPERACION_H_

#include "structs.h"

int inicializarOperacion(TDAWSOperacion *operacion, char *formato, char *nombre);

int getTime(TDAWS *ws, char *fecha, char por_consola);

int getMaxIdClient(TDAWS *ws, char por_consola);

int setMaxIdClient(TDAWS *ws, char por_consola);

int getClientById(TDAWS *ws, char por_consola, int id);

int setClientById(TDAWS *ws, char por_consola);

int getAllClients(TDAWS *ws, char por_consola);

int getAllOperations(TDAWS *ws, char por_consola);

int validateOperation(TDAWS *ws, char por_consola);

#endif /* TDAWSOPERACION_H_ */
