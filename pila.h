/*
 * pila.h
 *
 *  Created on: 8 Oct 2017
 *      Author: Yoel
 */

#ifndef PILA_H_
#define PILA_H_

	#if !defined(NULL)
		#define NULL 0
	#endif

	#if !defined(FALSE)
		#define FALSE 0
	#endif

	#if !defined(TRUE)
		#define TRUE 1
	#endif

	typedef struct TNodoPila{
		void* Elem;
		struct TNodoPila *Siguiente;
	} TNodoPila;

	typedef struct{
	TNodoPila *Tope;
	int TamanioDato;
	} TPila;

	/*P_Crear
	Pre: P no fue creada.
	Post: P creada y vacía. */
	void P_Crear(TPila *pP, int TamanioDato);

	/*P_Vaciar
	Pre: P creada.
	Post: P vacía. */
	void P_Vaciar(TPila *pP);

	/*P_Vacia
	Pre: P creada.
	Post: Si P está vacía devuelve TRUE, sino FALSE. */
	int P_Vacia(TPila P);

	/*P_Agregar
	Pre: P creada.
	Post: E se agregó como Tope de P.
	Devuelve FALSE si no pudo agregar E, sino devuelve TRUE.*/
	int P_Agregar(TPila *pP, void* pE);

	/*P_Sacar
	Pre: P creada y no vacia.
	Post: Se extrajo de P el tope y se devuelve en E.
	Si no pudo extraer el elemento (porque la pila estaba vacía) devuelve FALSE,
	sino devuelve TRUE.*/
	int P_Sacar(TPila *pP, void* pE);

#endif /* PILA_H_ */
