/*
 * TDAWS.C
 *
 *  Created on: 16 Oct 2017
 *      Author: Yoel
 */

#include <stdio.h>
#include <string.h>

#include "cola.h"
#include "lista.h"
#include "pila.h"
#include "TDAWS.h"
#include "TElemCliente.h"

#define path_config "SERVERTP2GRUPAL.conf"

int TDAWS_Crear(TDAWS * ws, char * cmd) {

	/*
	char tipo_op = 0; // 0 = POST; 1 = GET
	char tipo_formato = 0; // 0 = JSON; 1 = XML
	unsigned char i = 0;
	if (strcmp(argv[i], "-X") == 0) {
		// Verifico si es GET o POST
		i++;
		if (strcmp(argv[i], "GET") == 0)
			tipo_op++;
		else if (strcmp(argv[i], "POST") != 0) return -1;

		i++;
		if (strcmp(argv[i], "-H") == 0) {
			// Verifico si es JSON o XML
			i++;
			if (tipo_op == 0) {
				if (strcmp(argv[i], "\"Content-Type:application/json\"") == 0)
					tipo_formato++;
				else if (strcmp(argv[i], "\"Content-Type:application/xml\"") != 0) return -1;
			}
			else {
				if (strcmp(argv[i], "\"Accept:application/json\"") == 0)
					tipo_formato++;
				else if (strcmp(argv[i], "\"Accept:application/xml\"") != 0) return -1;
			}

			// Obtengo URL donde consumir el servicio
			i++;


			// Parseo la data
			i++;
			if (strcmp(argv[i], "-d") == 0) {
				// parsear mensaje
				i++;
			}
			else return -1;
		}
		else return -1;

	}
	else return -1;
	*/

	// OBTENER VALORES DE ARCHIVO DE CONFIGURACION

	char str[50];
	char *token;

	char *path_operaciones;
	char *path_clientes;
	char *path_log;

	FILE *arch_config = fopen(path_config,"r");

	for (unsigned int i = 0; i < 3; i++) {
		fgets(str, 50, arch_config);
		token = strtok(str, "=");
		if (strcmp(token, "pathOperaciones") == 0) {
			path_operaciones = strtok(NULL, "=");
		}
		else if (strcmp(token, "pathClientes") == 0) {
			path_clientes = strtok(NULL, "=");
		}
		else if (strcmp(token, "pathLog") == 0) {
			path_log = strtok(NULL, "=");
		}
		else {
			printf("El archivo de configuraci�n tiene valores incorrectos.\n");
			return -1;
		}
	}

	fclose(arch_config);

	// LISTA DE OPERACIONES DISPONIBLES

	ls_Crear(&ws->LOperaciones, 20);
	char operacion[20];
	FILE *arch_operaciones = fopen(path_operaciones,"r");
	while (fgets(operacion, 20, arch_operaciones) != NULL)
		ls_Insertar(&ws->LOperaciones, LS_SIGUIENTE, operacion);
	fclose(arch_operaciones);

	// LISTA DE TDAClientes

	ls_Crear(&ws->TClientes, sizeof(TElemCliente));
	TElemCliente *cliente = (TElemCliente*) malloc(sizeof(TElemCliente));
	char *linea_cliente;
	FILE *arch_clientes = fopen(path_clientes,"r");
	while (fgets(linea_cliente, sizeof(TElemCliente), arch_clientes) != NULL) {
		token = strtok(linea_cliente, ";");
		cliente->idCliente = atoi(token);
		token = strtok(NULL, ";");
		strcpy(cliente->Nombre, token);
		token = strtok(NULL, ";");
		strcpy(cliente->Apellido, token);
		token = strtok(NULL, ";");
		strcpy(cliente->Telefono, token);
		token = strtok(NULL, ";");
		strcpy(cliente->mail, token);
		token = strtok(NULL, ";");
		strcpy(cliente->fecha, token);
		ls_Insertar(&ws->TClientes, LS_SIGUIENTE, cliente);
	}
	fclose(arch_clientes);

	// COLA CON LAS OPERACIONES EJECUTADAS

	return 0;
}

int TDAWS_OperacionValida(TDAWS * ws) {

	return 0;
}

int TDAWS_Consumir(TDAWS * ws) {

	return 0;
}

int TDAWS_Destruir(TDAWS * ws) {

	return 0;
}