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

void imprimir_presentacion();

void imprimir_datos_personajes(personaje_t personaje, sombra_t sombra);

void imprimir_area_de_juego(juego_t juego);

#endif