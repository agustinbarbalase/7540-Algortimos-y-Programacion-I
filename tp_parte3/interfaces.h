#ifndef __INTERFACES__
#define __INTERFACES__

/*
	Biblioteca para trabajar con las interfaces del juego
*/

#include <stdio.h>
#include "la_sombra_de_mac.h"
#include "coordenadas_y_movimiento.h"
#include "personajes_y_niveles.h"
#include "constantes.h"

/*
	Pre: -
	Post: Muestra por pantalla la presentación 
*/
void imprimir_presentacion();

/*
	Pre: Recibimos al personaje y su sombra
	Post: Imprimimos por pantalla su informacion
*/
void imprimir_datos_personajes(personaje_t personaje, sombra_t sombra);

/* 
	Pre: Recibimos el juego
	Post: Imprimimos por pantalla, el terreno de juego. Eso incluye las paredes, los personajes,
	las herramientas y los obstaculos
*/
void imprimir_area_de_juego(juego_t juego);

#endif