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

bool hay_colision(nivel_t nivel, coordenada_t posicion);

void manejar_colisiones(juego_t* juego, char movimiento);

#endif