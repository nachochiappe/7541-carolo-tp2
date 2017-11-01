/*
 * parserXML.h
 *
 *  Created on: 28 oct. 2017
 *      Author: fernando
 */

#ifndef PARSEOENTRADA_H_
#define PARSEOENTRADA_H_

#include "lista.h"
#include "structs.h"

/*
 * Pre: recibe un puntero a TElemCliente y una cadena en formato XML
 * Post: parsea la cadena XML y la carga en la estructura TElemCliente
 */
void parseaClienteXML(TElemCliente *clienteNuevo, char *lineaXML);


/*
 * Pre: recibe un puntero a TElemCliente y una cadena en formato XML
 * Post: parsea la cadena XML y la carga en la estructura TElemCliente
 */
void parseaClienteJSON(TElemCliente *clienteNuevo, char *lineaJSON);

#endif /* PARSEOENTRADA_H_ */





