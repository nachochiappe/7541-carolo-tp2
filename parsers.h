/*
 * parsers.h
 *
 *  Created on: 28 Oct 2017
 *      Author: Yoel
 */

#include "structs.h"

#ifndef PARSERS_H_
#define PARSERS_H_

	int concatValue(void*value, char*res);

	int llavesXML(char*key, char*res, int cierraTag);

	int stringToXMLTags(char*key, void*value, char*xmlTag);

	int headerXML(char*XML);

	int clienteToXML(TElemCliente cli, char*clienteXML);

	int comillasJSON(char*key, int siguiente);

	int llavesJSON(char*strJSON);

	int addValueToJSON(char*key, void*value, char*strJSON, int next);

	int clienteToJSON(TElemCliente cli, char*clienteJSON);

#endif /* PARSERS_H_ */
