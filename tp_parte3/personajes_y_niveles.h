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

/* 
	Pre: Recibe por parametros una referencia a un struct tipo personaje_t
	y un struct de tipo coordenada_t
	Post: Asigna por referencia el struct coordenada_t
	a la componente posicion del personaje, siendo esta coordenada_t
*/
void inicializar_personaje(personaje_t* personaje, coordenada_t arranque_personaje);

/*
	Pre: Recibe por parametros una referencia a un struct tipo sombra_t y un struct
	de tipo coordenada_t
	Post: Asigna al struct sombra_t, una posicion.fila igual a la que se paso por
	parametro, pero una posicion.col diferente restando la maxima posicion horizontal
*/ 
void inicializar_sombra(sombra_t* sombra, coordenada_t arranque_sombra);

/* 
	Pre: Recibir una variable tipo coordenada_t, correspondiente al personaje
	Post: Retornar dicha variable como una coordenada correspondiente a la sombra
*/
coordenada_t calcular_arranque_sombra(coordenada_t coordenada);

/*
	Pre: Recibimos el juego, dos coordenadas asociadas al personaje y su sombra 
	ambos por referencia
	Post: Generamos una dichas posiciones de arranque comprobando que no haya
	colisiones de ningun tipo en dichas coordenadas generadas
*/
void generar_coordenadas_personajes(
	juego_t juego, 
	coordenada_t* arranque_personaje, 
	coordenada_t* arranque_sombra
);

/*
	Pre: Recibimos un nivel por referencia, un numero de nivel y las coordenadas del personaje 
	y su sombra. Junto con las configuraciones
	Post: Generamos los obstaculos y herramientas de acuerdo al numero de nivel
*/
void inicializar_nivel(nivel_t* nivel, int numero_nivel, coordenada_t personaje, coordenada_t sombra, config_t configuraciones[MAX_CONFIG]);

#endif