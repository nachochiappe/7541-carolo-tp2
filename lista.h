/*
 * Lista.h
 *
 *  Created on: 8 Oct 2017
 *      Author: Yoel
 */

#ifndef Lista_H_
#define Lista_H_

	#if !defined(NULL)
		#define NULL 0
	#endif

	#if !defined(FALSE)
		#define FALSE 0
	#endif

	#if !defined(TRUE)
		#define TRUE 1
	#endif

	typedef enum{
		LS_PRIMERO,
		LS_SIGUIENTE,
		LS_ANTERIOR
	} TMovimiento_Ls;

	typedef struct TNodoSimple{
		void* Elem;
		struct TNodoSimple *Siguiente;
	} TNodoSimple;

	typedef struct{
		TNodoSimple *Primero, *Corriente;
		int TamanioDato;
	} TLista;

	/* ls_Crear
	Pre: Ls no fue creada.
	Post: Ls creada y vac�a */
	void ls_Crear(TLista *pLs, int TamanioDato);

	/* ls_Vaciar
	Pre: Ls creada.
	Post: Ls vac�a.*/
	void ls_Vaciar(TLista *pLs);

	/* ls_Vacia
	Pre: Ls creada.
	Post: Si Ls tiene elementos devuelve FALSE sino TRUE.*/
	int ls_Vacia(TLista Ls);

	/* ls_ElemCorriente
	Pre: Ls creada y no vac�a.
	Post: Se devuelve en E el elemento corriente de la lista.*/
	void ls_ElemCorriente(TLista Ls, void* pE);

	/* ls_ModifCorriente
	Pre: Ls creada y no vac�a.
	Post: El contenido del elemento actual quedo actualizado con E. */
	void ls_ModifCorriente(TLista *pLs, void* pE);

	/* ls_MoverCorriente
	Pre: Ls creada y no vac�a.
	Post: Si Ls est� vac�a, devuelve FALSE. Sino:
	Si M = LS_PRIMERO, el nuevo elemento corriente es el primero. Devuelve TRUE
	Si M = LS_SIGUIENTE, el nuevo elemento corriente es el siguiente al
	anterior. Si estaba en el �ltimo elemento, devuelve FALSE, sino TRUE.
	Si M = LS_ANTERIOR, devuelve FALSE. */
	int ls_MoverCorriente(TLista *pLs, TMovimiento_Ls M);

	/* ls_BorrarCorriente
	Pre: Ls creada y no vac�a.
	Post: Se elimin� el elemento corriente, El nuevo elemento es el siguiente o
	el anterior si el corriente era el �ltimo elemento.*/
	void ls_BorrarCorriente(TLista *pLs);

	/* ls_Insertar
	Pre: Ls creada.
	Post: E se agreg� a la lista y es el actual elemento corriente.
	Si M=LS_PRIMERO: se insert� como primero de la lista.
	Si M=LS_SIGUIENTE: se insert� despu�s del elemento corriente.
	Si M=LS_ANTERIOR: se insert� antes del elemento corriente.
	Si pudo insertar el elemento devuelve TRUE, sino FALSE.*/
	int ls_Insertar(TLista *pLs, TMovimiento_Ls M, void* E);

#endif /* Lista_H_ */
