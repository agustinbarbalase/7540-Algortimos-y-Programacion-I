#ifndef __ELEMENTOS__
#define __ELEMENTOS__

/*
	Biblioteca para trabajar con elementos. Ya sea buscar, agregar o eliminar
*/

#include "la_sombra_de_mac.h"
#include "coordenadas_y_movimiento.h"
#include "constantes.h"

int buscar_elemento(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t posicion);

int buscar_pared(coordenada_t paredes[MAX_PAREDES], int tope_paredes, coordenada_t posicion);

int buscar_puerta(elemento_t elementos[MAX_ELEMENTOS], int tope);

int buscar_escalera(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t coordenada);

void agregar_elemento(elemento_t elementos[MAX_ELEMENTOS], int* tope, elemento_t elemento);

void eliminar_elemento(elemento_t elementos[MAX_ELEMENTOS], int* tope, int pos_buscado);

#endif