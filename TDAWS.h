/*
 * TdaWS.h
 *
 *  Created on: 16 Oct 2017
 *      Author: Yoel
 */

#ifndef TDAWS_H_
#define TDAWS_H_



typedef struct TDAWS{
	TDAWSOperacion TOperacion; /*Operaci�n actual que se consume*/
	TLista LOperaciones; /* Lista con las operaciones disponibles */
	TLista TClientes; /*Lista de TDAClientes con cantidad*/
	TCola CEjecucion; /*Cola con las operaciones ejecutadas*/
} TDAWS;

/* PRE: ninguna
 POST: inicializa la estructura de servicios y de clientes para poder consumir los servicios
*/
int TDAWS_Crear(TDAWS * ws, char * cmd);

/* PRE: TDAWS Creado
 POST: valida que la operaci�n a ejecutar se encuentre en la definici�n del servicio.
*/
int TDAWS_OperacionValida(TDAWS * ws);

/* PRE: TDAWS Creado
 POST: ejecuta una operaci�n indicada al servicio para impactar en la estructura de
clientes
*/
int TDAWS_Consumir(TDAWS * ws);

/* PRE: TDAWS Creado
 POST: libera los recursos del servicio y la base de clientes y actualiza los cambios en los
archivos donde persisten los datos.
*/
int TDAWS_Destruir(TDAWS * ws);

#endif /* TDAWS_H_ */
