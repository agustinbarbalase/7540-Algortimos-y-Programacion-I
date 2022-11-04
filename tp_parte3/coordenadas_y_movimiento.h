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

/* 
	Pre: Recibe por parametros dos structs de tipo coordenada_t
	Post: Retorna true, si las componentes (fila y columna) 
	de ambos structs son iguales, en caso contrario un false 
*/
bool coordenadas_iguales(coordenada_t a, coordenada_t b);

/*
	Pre: Recibe por parametros un struct de tipo coordenada_t y dos varaibles de tipo int
	Post: Retorna true si al llamar a las funciones verificar_alto y verificar_ancho, ambas
	retorna true, en caso contrario retorna false
*/
bool esta_dentro_rango(coordenada_t posicion, int min_alto, int max_alto, int min_ancho, int max_ancho);

/* 
	Pre: Recibe dos variables de tipo int
	Post: Retorna un struct de tipo coordenada_t con valores aleatorios, y dentro del rango
	pasado por parametro
*/
coordenada_t coordenada_aleatoria(int min_alto, int max_alto, int min_ancho, int max_ancho);

/*
	Pre: Recibimos dos coordenandas
	Post: Retornamos la distancia manhattan entre esas dos coordenadas
*/
int distancia_manhattan(coordenada_t a, coordenada_t b);

/* 
	Pre: Recibe por parametros una variable de tipo char
	Post: Retorna un true si la variable es igual a alguna de las siguientes constantes:
	- ARRIBA
	- ABAJO
	- IZQUIERDA
	- DERECHA
	- VIDA
	En caso contrario, retorna un false
*/
bool es_movimiento_valido(char movimiento);

/* 
	Pre: Recibe por parametro una referencia a una variable de tipo char
	Post: Espera que el usuario ingrese un caracter validado por la funcion 
	es_movimiento_valido() y si este valido asigna a la referencia ese valor, en caso
	contrario, el procedimiento imprimira por pantalla "¡Movimiento invalido!", hasta
	que el usuario ingrese un caracter valido por es_movimiento_valido()
*/
void pedir_movimiento(char* ref_movimiento);

/* 
	Pre: Recibe por parametros dos referencias de tipo personaje_t y sombra_t, y una variable
	de tipo char
	Post: Si se valida el movimiento y dependiendo del mismo, el procedimiento llamara al 
	procedimiento mover_verticalmente() o mover_horizontalmente()
*/
void mover_personaje(juego_t* juego, char movimiento);

#endif