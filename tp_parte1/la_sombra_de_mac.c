#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "la_sombra_de_mac.h"

#define RESET_COLOR  "\x1b[0m"

#define RED   "\x1b[31m"
#define BLUE  "\x1b[34m"

/* 
	Pre: Recibe por parametros dos structs de tipo coordenada_t
	Post: Retorna true, si las componentes (fila y columna) 
	de ambos structs son iguales, en caso contrario un false 
*/

bool coordenadas_iguales(coordenada_t a, coordenada_t b) {
	if((a.col == b.col) && (a.fila == b.fila)) {
		return true;
	} else {
		return false;
	}
}

/* 
	Pre: Recibe por parametros una referencia a un struct tipo personaje_t
	y un struct de tipo coordenada_t
	Post: Asigna por referencia el struct coordenada_t
	a la componente posicion del personaje, siendo esta coordenada_t
*/

void inicializar_personaje(personaje_t* ref_personaje, coordenada_t arranque_personaje) {
	(*ref_personaje).posicion = arranque_personaje;
	(*ref_personaje).vida = 3;
	(*ref_personaje).puntos = 0;
	(*ref_personaje).tiene_llave = false;
	(*ref_personaje).interruptor_apretado = false;
}

/*
	Pre: Recibe por parametros una referencia a un struct tipo sombra_t y un struct
	de tipo coordenada_t
	Post: Asigna al struct sombra_t, una posicion.fila igual a la que se paso por
	parametro, pero una posicion.col diferente restando la maxima posicion horizontal
*/ 

void inicializar_sombra(sombra_t* ref_sombra, coordenada_t arranque_sombra) {
	(*ref_sombra).posicion.fila = arranque_sombra.fila;
	(*ref_sombra).posicion.col = arranque_sombra.col;
	(*ref_sombra).esta_viva = true;
}

/* 
	Pre: Recibe por parametros una variable de tipo char
	Post: Retorna un true si la variable es igual a alguna de las siguientes constantes:
	- ARRIBA
	- ABAJO
	- IZQUIERDA
	- DERECHA
	En caso contrario, retorna un false
*/

bool es_movimiento_valido(char movimiento) {
	switch (movimiento) {
		case ARRIBA:
			return true;
		break;
		case ABAJO:
			return true;
		break;
		case IZQUIERDA:
			return true;
		break;
		case DERECHA:
			return true;
		break;
		default:
			return false;
	}
}

/* 
	Pre: Recibe por parametro una referencia a una variable de tipo char
	Post: Espera que el usuario ingrese un caracter validado por la funcion 
	es_movimiento_valido() y si este valido asigna a la referencia ese valor, en caso
	contrario, el procedimiento imprimira por pantalla "¡Movimiento invalido!", hasta
	que el usuario ingrese un caracter valido por es_movimiento_valido()
*/

void pedir_movimiento(char* ref_movimiento) {
	char movimiento_ingresado;

	do {
		printf("Ingresar un movimiento: ");
		scanf(" %c", &movimiento_ingresado);
		if(!es_movimiento_valido(movimiento_ingresado)) {
			printf("¡Movimiento invalido!\n");
		}
	} while(!es_movimiento_valido(movimiento_ingresado));
	

	*ref_movimiento = movimiento_ingresado;
}

/* 
	Pre: Recibe dos variables de tipo int
	Post: Retorna true si la variable fila es mayor igual a 0 y menor que la variable
	max_alto, en caso contrario retorna false
*/

bool verificar_alto(int fila, int max_alto) {
	return ((fila < max_alto) && (fila >= 0));
}

/* 
	Pre: Recibe dos variables de tipo int
	Post: Retorna true si la variable col es mayor igual a 0 y menor que la variable
	max_ancho, en caso contrario retorna false
*/

bool verificar_ancho(int col, int max_ancho) {
	return ((col < max_ancho) && (col >= 0));
}

/*
	Pre: Recibe por parametros un struct de tipo coordenada_t y dos varaibles de tipo int
	Post: Retorna true si al llamar a las funciones verificar_alto y verificar_ancho, ambas
	retorna true, en caso contrario retorna false
*/

bool esta_dentro_rango(coordenada_t posicion, int max_alto, int max_ancho) {
	if(verificar_alto(posicion.fila, max_alto) && verificar_ancho(posicion.col, max_ancho)) {
		return true;
	} else {
		return false;
	}
}

/* 
	Pre: Recibe por parametros dos referencias de tipo personaje_t y sombra_t, y una variable
	de tipo char
	Post: Asigna valores a las referencias personaje_t y sombra_t, dependiendo del valor
	de la variable de tipo char
*/

void mover_verticalmente(personaje_t* ref_personaje, sombra_t* ref_sombra, char movimiento) {
	coordenada_t proxima_coordenada_personaje = (*ref_personaje).posicion;
	coordenada_t proxima_coordenada_sombra = (*ref_sombra).posicion;

	switch (movimiento) {
		case ARRIBA:
			proxima_coordenada_personaje.fila -= 1;
			proxima_coordenada_sombra.fila -= 1;

			if(esta_dentro_rango(proxima_coordenada_personaje, MAX_FILAS, MAX_COLUMNAS)) {
				(*ref_personaje).posicion.fila -= 1;
			}

			if (esta_dentro_rango(proxima_coordenada_sombra, MAX_FILAS, MAX_COLUMNAS)) {
				(*ref_sombra).posicion.fila -= 1;
			}

		break;
		case ABAJO:
			proxima_coordenada_personaje.fila += 1;
			proxima_coordenada_sombra.fila += 1;

			if(esta_dentro_rango(proxima_coordenada_personaje, MAX_FILAS, MAX_COLUMNAS)) {
				(*ref_personaje).posicion.fila += 1;
			}

			if (esta_dentro_rango(proxima_coordenada_sombra, MAX_FILAS, MAX_COLUMNAS)) {
				(*ref_sombra).posicion.fila += 1;
			}

		break;
	}
}

/* 
	Pre: Recibe por parametros dos referencias de tipo personaje_t y sombra_t, y una variable
	de tipo char
	Post: Asigna valores diferentes a las referencias personaje_t y sombra_t, dependiendo 
	del valor de la variable de tipo char
*/

void mover_horizontalmente(personaje_t* ref_personaje, sombra_t* ref_sombra, char movimiento) {
	coordenada_t proxima_coordenada_personaje = (*ref_personaje).posicion;
	coordenada_t proxima_coordenada_sombra = (*ref_sombra).posicion;

	switch (movimiento) {
		case IZQUIERDA:
			proxima_coordenada_personaje.col -= 1;
			proxima_coordenada_sombra.col += 1;

			if(esta_dentro_rango(proxima_coordenada_personaje, MAX_FILAS, MAX_COLUMNAS)) {
				(*ref_personaje).posicion.col -= 1;
			}

			if (esta_dentro_rango(proxima_coordenada_sombra, MAX_FILAS, MAX_COLUMNAS)) {
				(*ref_sombra).posicion.col += 1;
			}

		break;
		case DERECHA:
			proxima_coordenada_personaje.col += 1;
			proxima_coordenada_sombra.col -= 1;

			if(esta_dentro_rango(proxima_coordenada_personaje, MAX_FILAS, MAX_COLUMNAS)) {
				(*ref_personaje).posicion.col += 1;
			}

			if(esta_dentro_rango(proxima_coordenada_sombra, MAX_FILAS, MAX_COLUMNAS)) {
				(*ref_sombra).posicion.col -= 1;
			}

		break;
	}
}

/* 
	Pre: Recibe por parametros dos referencias de tipo personaje_t y sombra_t, y una variable
	de tipo char
	Post: Si se valida el movimiento y dependiendo del mismo, el procedimiento llamara al 
	procedimiento mover_verticalmente() o mover_horizontalmente()
*/

void mover_personaje(personaje_t* ref_personaje, sombra_t* ref_sombra, char movimiento) {
	if(es_movimiento_valido(movimiento)) {
		if((movimiento == ARRIBA) || (movimiento == ABAJO)) {
			mover_verticalmente(ref_personaje, ref_sombra, movimiento);
		} else {
			mover_horizontalmente(ref_personaje, ref_sombra, movimiento);
		}
	}
}

/* 
	Pre: Recibe dos variables de tipo int
	Post: Retorna un struct de tipo coordenada_t con valores aleatorios, y dentro del rango
	pasado por parametro
*/

coordenada_t coordenada_aleatoria(int max_alto, int max_ancho) {
	coordenada_t coordenada_retorno;

	coordenada_retorno.fila = rand() % max_alto;
	coordenada_retorno.col = rand() % max_ancho;

	return coordenada_retorno;
}

/* 
	Pre: Recibe un vector de elemento_t, un int y un struct coordenada_t
	Post: Retorna la posicion dentro del vector elemento_t, si cuyo elemento_t
	comparte componente posicion con la coordenada_t pasada por parametro. En caso contrario
	retorna -1 
*/

int buscar_elemento(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t posicion) {
	int pos_encontrada = -1;
	bool encontrado = false;

	int i = 0;

	while(i < tope && !encontrado) {
		if(coordenadas_iguales(elementos[i].posicion, posicion)) {
			pos_encontrada = i;
			encontrado = true;
		}
		i++;
	}

	return pos_encontrada;
}

/* 
	Pre: Recibe un struct de tipo juego_t
	Post: Imprime por pantalla un cuadrado de tamaño MAX_FILAS * MAX_COLUMNAS, y en aquellas
	posiciones que comparte coordenadas con los personajes, imprime una 'M' o una 'B', sino 
	imprime un '*'
*/

void imprimir_terreno(juego_t juego) {
	coordenada_t pos_actual;

	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < MAX_COLUMNAS; j++) {
			pos_actual.fila = i;
			pos_actual.col = j;

			if(coordenadas_iguales(juego.personaje.posicion, pos_actual)) {
				printf(RED" M " RESET_COLOR);
			} else if(coordenadas_iguales(juego.sombra.posicion, pos_actual)) {
				printf(BLUE" B " RESET_COLOR);
			} else {
				printf(" * " RESET_COLOR);
			}
		}
		printf("\n");
	}
}
