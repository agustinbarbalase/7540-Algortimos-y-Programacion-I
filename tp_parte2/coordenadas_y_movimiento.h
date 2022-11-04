#ifndef __COORDENADAS_Y_MOVIMIENTO__
#define __COORDENADAS_Y_MOVIMIENTO__

/*
	Biblioteca para trabajar con coordenadas y los movimientos de los personajes
*/

#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "la_sombra_de_mac.h"
#include "elementos.h"
#include "constantes.h"

bool coordenadas_iguales(coordenada_t a, coordenada_t b);

bool esta_dentro_rango(coordenada_t posicion, int min_alto, int max_alto, int min_ancho, int max_ancho);

coordenada_t coordenada_aleatoria(int min_alto, int max_alto, int min_ancho, int max_ancho);

int distancia_manhattan(coordenada_t a, coordenada_t b);

void pedir_movimiento(char* ref_movimiento);

bool es_movimiento_valido(char movimiento);

void mover_personaje(juego_t* juego, char movimiento);

#endif