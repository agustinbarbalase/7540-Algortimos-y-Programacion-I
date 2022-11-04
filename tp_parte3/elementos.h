#ifndef __ELEMENTOS__
#define __ELEMENTOS__

/*
	Biblioteca para trabajar con elementos. Ya sea buscar, agregar o eliminar
*/

#include "la_sombra_de_mac.h"
#include "coordenadas_y_movimiento.h"
#include "constantes.h"

/* 
	Pre: Recibe un vector de elemento_t, un int y un struct coordenada_t
	Post: Retorna la posicion dentro del vector elemento_t, si cuyo elemento_t
	comparte componente posicion con la coordenada_t pasada por parametro. En caso contrario
	retorna -1 
*/
int buscar_elemento(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t posicion);

/* 
	Pre: Recibe un vector de paredes con su tope y una coordenada_t
	Post: Devuelve la posicion del vector en donde la posicion pasa como parametro coicide 
	con una que conicida en el vector, en caso contrario devuelve -1
*/
int buscar_pared(coordenada_t paredes[MAX_PAREDES], int tope_paredes, coordenada_t posicion);

/*
	Pre: Recibe un vector de tipo elemento_t con su tope
	Post: Devuelve la posicion donde esta la puerta
*/
int buscar_puerta(elemento_t elementos[MAX_ELEMENTOS], int tope);

/*
	Pre: Recibe un vector de tipo elemento_t con su tope y una posicion
	Post: Devuelve la posicion donde haya una escalera en la posicion que pasamos por 
	parametro, en caso de que no haya devolvemos -1
*/
int buscar_escalera(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t coordenada);

/* 
	Pre: Recibe un vector de elemento_t con su tope por referencia y un elemento_t
	Post: Agrega un elemento en el vector y aumenta su tope
*/
void agregar_elemento(elemento_t elementos[MAX_ELEMENTOS], int* tope, elemento_t elemento);

/* 
	Pre: Recibe un vector de elementos con su tope por referencia y un int
	Post: Elimina un elemento en el vector, si es que pos_buscado es diferente a -1. Y reduce
	su tope 
*/
void eliminar_elemento(elemento_t elementos[MAX_ELEMENTOS], int* tope, int pos_buscado);

#endif