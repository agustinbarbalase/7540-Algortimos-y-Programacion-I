#ifndef __PERSONAJES_Y_NIVELES__
#define __PERSONAJES_Y_NIVELES__

/*
	Biblioteca que se encarga de generar los niveles y a los personajes
*/

#include <stdbool.h>
#include "la_sombra_de_mac.h"
#include "coordenadas_y_movimiento.h"
#include "elementos.h"
#include "colisiones.h"
#include "utiles.h"
#include "constantes.h"

void inicializar_personaje(personaje_t* personaje, coordenada_t arranque_personaje);

void inicializar_sombra(sombra_t* sombra, coordenada_t arranque_sombra);

void generar_coordenadas_personajes(
	juego_t juego, 
	coordenada_t* arranque_personaje, 
	coordenada_t* arranque_sombra
);

coordenada_t calcular_arranque_sombra(coordenada_t coordenada);

void inicializar_nivel(nivel_t* nivel, int numero_nivel, coordenada_t personaje, coordenada_t sombra);

#endif