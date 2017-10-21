/*
 * TElemCliente.h
 *
 *  Created on: 16 Oct 2017
 *      Author: Yoel
 */

#ifndef TELEMCLIENTE_H_
#define TELEMCLIENTE_H_

typedef struct TElemCliente {
	int idCliente;
	char Nombre[20];
	char Apellido[20];
	char Telefono[20];
	char mail[20];
	char fecha[20];
} TElemCliente;

#endif /* TELEMCLIENTE_H_ */
