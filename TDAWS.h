/*
 * TdaWS.h
 *
 *  Created on: 16 Oct 2017
 *      Author: Yoel
 */

#ifndef TDAWS_H_
#define TDAWS_H_

#include "structs.h"

/* PRE: ninguna
 POST: inicializa la estructura de servicios y de clientes para poder consumir los servicios
*/
int TDAWS_Crear(TDAWS * ws, char ** cmd);

/* PRE: TDAWS Creado
 POST: valida que la operación a ejecutar se encuentre en la definición del servicio.
*/
int TDAWS_OperacionValida(TDAWS * ws);

/* PRE: TDAWS Creado
 POST: ejecuta una operación indicada al servicio para impactar en la estructura de
clientes
*/
int TDAWS_Consumir(TDAWS * ws);

/* PRE: TDAWS Creado
 POST: libera los recursos del servicio y la base de clientes y actualiza los cambios en los
archivos donde persisten los datos.
*/
int TDAWS_Destruir(TDAWS * ws);

#endif /* TDAWS_H_ */
