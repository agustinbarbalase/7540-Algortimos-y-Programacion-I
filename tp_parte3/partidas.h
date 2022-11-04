#ifndef __PARTIDAS__
#define __PARTIDAS__

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "programas.h"

#define MAX_NOMBRE  100
#define MAX_PARTIDA 100
#define MAX_GANO      3

typedef struct partida {
	char jugador[MAX_NOMBRE];
	int nivel_llegado;
	int puntos;
	int vidas_restantes;
	bool gano;
} partida_t;

/*
	Pre: Recibimos dos archivos uno en modo leer y el otro en modo escribir. Y struct
	partida_t no vacio
	Post: Agregamos en el archivo la partida respetando el orden alfabetico y pre establecido
	del archivo
*/
void agregar_ordenandamente(FILE* partida_arch, FILE* partida_aux, partida_t nueva_partida);

/*
	Pre: Recibimos dos archivos uno en modo leer y el otro en modo escribir. Y un nombre
	de jugador, que puede estar o no en el archivo leido
	Post: Eliminamos del archivo leido, el jugador que pasamos por parametro
*/
void eliminar_ordenadamente(FILE* partida_arch, FILE* partida_aux, char nombre_jugador[]);

/*
	Pre: Recibimos dos archivos, uno en modo leer y el otro en modo escribir
	Post: Leemos del archivo para leer, las partidas y las guardamos en un vector
	para ordenarlas, y esos elementos del vector los escribimos en el otro archivo
*/
void ordenar_por_jugador(FILE* partida_arch, FILE* partida_aux);

#endif