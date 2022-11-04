#ifndef __COLISIONES__
#define __COLISIONES__

/*
	Biblioteca donde se manejan las colisiones de los personajes
*/

#include <stdbool.h>
#include <math.h>
#include "la_sombra_de_mac.h"
#include "coordenadas_y_movimiento.h"
#include "personajes_y_niveles.h"
#include "elementos.h"
#include "constantes.h"

/*
	Pre: Recibe un nivel_t y una coordenada
	Post Devuelve true si hay colision con al menos una pared, una herramienta o un obstaculo.
	En caso contrario devuelve false
*/
bool hay_colision(nivel_t nivel, coordenada_t posicion);

/*
	Pre: Recibimos una referencia del juego y el ultimo movimiento
	Post: Llamamamos a los procedimiento que manejan las colisiones del personaje y la 
	sombra
*/
void manejar_colisiones(juego_t* juego, char movimiento);

#endif