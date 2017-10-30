/*
 * parsers.c
 *
 *  Created on: 28 Oct 2017
 *      Author: Yoel
 */

#include "Cola.h"
#include "parsers.h"
#include "main.h"
#include <malloc.h>
#include <memory.h>
#include <string.h>

int concatValue(void*value, char*res){
	char* strAux;
	strAux = (char*)value;
	strcat(res,strAux);
	return RES_OK;
}

int llavesXML(char*key, char*res, int cierraTag){
	strcat(res,"<");
	strcat(res,key);
	if (cierraTag == TRUE)
		strcat(res,"/");
	strcat(res,">");
	return RES_OK;
}

int stringToXMLTags(char*key, void*value, char*xmlTag){
	char strAux[255] = "";
	//printf("valor: %s \n" ,(char*)value);
	llavesXML(key,strAux,FALSE);
	concatValue(value,strAux);
	llavesXML(key,strAux,TRUE);
	strcat(xmlTag,strAux);
	return RES_OK;
}

int headerXML(char*XML){
	char header[50] = "'<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	strcat(XML,header);
	return RES_OK;
}

int clienteToXML(TElemCliente cli, char*clienteXML){
	llavesXML("Cliente",clienteXML,FALSE);
	//char* id = (char*)cli.idCliente;
	//printf(id);

	//stringToXMLTags("id",id,clienteXML);
	stringToXMLTags("Nombre",cli.Nombre,clienteXML);
	stringToXMLTags("Apellido",cli.Apellido,clienteXML);
	stringToXMLTags("Telefono",cli.Telefono,clienteXML);
	stringToXMLTags("Mail",cli.mail,clienteXML);
	stringToXMLTags("Time",cli.fecha,clienteXML);
	llavesXML("Cliente",clienteXML,TRUE);
	return RES_OK;
}

int comillasJSON(char*res, int siguiente){
	char strAux[255] = "";
	strcat(strAux,"\"");
	strcat(strAux,res);
	strcat(strAux,"\"");
	if (siguiente == TRUE)
		strcat(strAux,",");
	strcpy(res,strAux);
	return RES_OK;
}

int llavesJSON(char*strJSON){
	char strAux[255] = "{";
	strcat(strAux,strJSON);
	strcat(strAux,"}");
	strcpy(strJSON,strAux);
	return RES_OK;
}

int addValueToJSON(char*key, void*value, char*strJSON, int next){
	char strAux[255] = "";
	strcat(strJSON,key);
	strcat(strJSON,":");
	//printf(value);
	concatValue(value,strAux);
	comillasJSON(strAux,next);
	//printf("%s\n",strAux);
	strcat(strJSON,strAux);
	return RES_OK;
}

int clienteToJSON(TElemCliente cli, char*clienteJSON){
	//addValueToJSON("Id",(void*)cli.idCliente,clienteJSON,TRUE);
	addValueToJSON("Nombre",cli.Nombre,clienteJSON,TRUE);
	addValueToJSON("Apellido",cli.Apellido,clienteJSON,TRUE);
	addValueToJSON("Telefono",cli.Telefono,clienteJSON,TRUE);
	addValueToJSON("Mail",cli.mail,clienteJSON,TRUE);
	addValueToJSON("Time",cli.fecha,clienteJSON,FALSE);
	llavesJSON(clienteJSON);//encierro con llaves
	return RES_OK;
}
