/*
 * pila.c
 *
 *  Created on: 8 Oct 2017
 *      Author: Yoel
 */

#include "Pila.h"
#include <malloc.h>
#include <memory.h>

/*P_Crear
Pre: P no fue creada.
Post: P creada y vacía. */
void P_Crear(TPila *pP, int TamanioDato){
	pP->Tope = NULL;
	pP->TamanioDato = TamanioDato;
}

/*P_Vaciar
Pre: P creada.
Post: P vacía. */
void P_Vaciar(TPila *pP){
	TNodoPila *pAux = pP->Tope;
	TNodoPila *pSig;
	while (pAux){
		pSig = pAux->Siguiente;
		free(pAux->Elem);
		free(pAux);
		pAux = pSig;
	}
	pP->Tope= NULL;
}

/*P_Vacia
Pre: P creada.
Post: Si P está vacía devuelve TRUE, sino FALSE. */
int P_Vacia(TPila P){
	return (P.Tope==NULL);
}

/*P_Agregar
Pre: P creada.
Post: E se agregó como Tope de P.
Devuelve FALSE si no pudo agregar E, sino devuelve TRUE.*/
int P_Agregar(TPila *pP, void* pE){
	TNodoPila *pNodo = (TNodoPila*) malloc(sizeof(TNodoPila));
	if (!pNodo)
	return FALSE;
	else{
		pNodo->Siguiente = pP->Tope;
		pP->Tope = pNodo;
		pNodo->Elem = malloc (pP->TamanioDato);
		memcpy(pNodo->Elem, pE, pP->TamanioDato);
		return TRUE;
	}
}

/*P_Sacar
Pre: P creada y no vacia.
Post: Se extrajo de P el tope y se devuelve en E.
Si no pudo extraer el elemento (porque la pila estaba vacía) devuelve FALSE,
sino devuelve TRUE.*/
int P_Sacar(TPila *pP, void* pE){
	TNodoPila *pAux = pP->Tope;
	pP->Tope = pP->Tope->Siguiente;
	memcpy(pE, pAux->Elem, pP->TamanioDato);
	free(pAux->Elem);
	free(pAux);
	return TRUE;
}
