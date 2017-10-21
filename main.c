/*
 * main.c
 *
 *  Created on: 8 Oct 2017
 */

#include <stdlib.h>

#include "TDAWS.h"

int main (int argc, char *argv[]) {

	TDAWS *ws = (TDAWS*) malloc(sizeof(TDAWS));

	if (!ws) return -1;

	if (TDAWS_Crear(ws, argv[1]) != 0) return -1;
	if (TDAWS_OperacionValida(ws) != 0) return -1;
	if (TDAWS_Consumir(ws) != 0) return -1;
	if (TDAWS_Destruir(ws) != 0) return -1;

	return 0;
}
