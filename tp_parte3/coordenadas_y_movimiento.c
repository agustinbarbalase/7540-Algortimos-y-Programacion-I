#include "coordenadas_y_movimiento.h"

/* 
	Pre: Recibe por parametros dos structs de tipo coordenada_t
	Post: Retorna true, si las componentes (fila y columna) 
	de ambos structs son iguales, en caso contrario un false 
*/
bool coordenadas_iguales(coordenada_t a, coordenada_t b) {
	return (a.col == b.col) && (a.fila == b.fila);
}

/* 
	Pre: Recibe dos variables de tipo int
	Post: Retorna true si la variable fila es mayor igual a 0 y menor que la variable
	max_alto, en caso contrario retorna false
*/
bool verificar_alto(int fila, int min_alto, int max_alto) {
	return ((fila <= max_alto) && (fila >= min_alto));
}

/* 
	Pre: Recibe dos variables de tipo int
	Post: Retorna true si la variable col es mayor igual a 0 y menor que la variable
	max_ancho, en caso contrario retorna false
*/
bool verificar_ancho(int col, int min_ancho, int max_ancho) {
	return ((col <= max_ancho) && (col >= min_ancho));
}

/*
	Pre: Recibe por parametros un struct de tipo coordenada_t y dos varaibles de tipo int
	Post: Retorna true si al llamar a las funciones verificar_alto y verificar_ancho, ambas
	retorna true, en caso contrario retorna false
*/
bool esta_dentro_rango(coordenada_t posicion, int min_alto, int max_alto, int min_ancho, int max_ancho) {
	return (
		verificar_alto(posicion.fila, min_alto, max_alto) &&
		verificar_ancho(posicion.col, min_ancho, max_ancho)
	);
}

/* 
	Pre: Recibe dos variables de tipo int
	Post: Retorna un struct de tipo coordenada_t con valores aleatorios, y dentro del rango
	pasado por parametro
*/
coordenada_t coordenada_aleatoria(int min_alto, int max_alto, int min_ancho, int max_ancho) {
	coordenada_t coordenada_retorno;

	coordenada_retorno.fila = (rand() % max_alto) + min_alto;
	coordenada_retorno.col = (rand() % max_ancho) + min_ancho;

	return coordenada_retorno;
}

/*
	Pre: Recibimos dos coordenandas
	Post: Retornamos la distancia manhattan entre esas dos coordenadas
*/
int distancia_manhattan(coordenada_t a, coordenada_t b) {
	int diferencial_x = abs(b.fila - a.fila);
	int diferencial_y = abs(b.col - a.col);

	return (diferencial_x + diferencial_y);
}

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
		case VIDA:
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
void pedir_movimiento(char* movimiento) {
	char movimiento_ingresado;

	do {
		printf("Ingresar un movimiento: ");
		scanf(" %c", &movimiento_ingresado);
		if(!es_movimiento_valido(movimiento_ingresado)) {
			printf("¡Movimiento invalido!\n");
		}
	} while(!es_movimiento_valido(movimiento_ingresado));
	

	*movimiento = movimiento_ingresado;
}

/*
	Pre: Recibimos un movimento, un nivel, al personaje y su sombra ambos por referencia
	Post: Movemos a los personaje de manera espacial (posicion) si es posible, de lo contrario
	permanecen igual 
*/
void mover_espacialemente(char movimiento, nivel_t nivel, personaje_t* personaje, sombra_t* sombra) {
	coordenada_t proxima_coordenada_personaje = (*personaje).posicion;
	coordenada_t proxima_coordenada_sombra = (*sombra).posicion;

	switch(movimiento) {
		case ARRIBA:
			proxima_coordenada_personaje.fila -= 1;
			proxima_coordenada_sombra.fila -= 1;
		break;
		case ABAJO:
			proxima_coordenada_personaje.fila += 1;
			proxima_coordenada_sombra.fila += 1;
		break;
		case DERECHA:
			proxima_coordenada_personaje.col += 1;

			if(!((*personaje).interruptor_apretado)) {	
				proxima_coordenada_sombra.col -= 1;
			} else {
				proxima_coordenada_sombra.col += 1;
			}
		break;
		case IZQUIERDA:
			proxima_coordenada_personaje.col -= 1;
			
			if(!((*personaje).interruptor_apretado)) {	
				proxima_coordenada_sombra.col += 1;
			} else {
				proxima_coordenada_sombra.col -= 1;
			}
		break;
	}

	if((
		(
			buscar_pared(nivel.paredes, nivel.tope_paredes, proxima_coordenada_personaje) == -1 ||
			buscar_escalera(nivel.herramientas, nivel.tope_herramientas, proxima_coordenada_personaje) != -1
		) && 
		(esta_dentro_rango(proxima_coordenada_personaje, 0, MAX_FILAS - 1, 0, MAX_COLUMNAS - 1))
	)) {
		(*personaje).posicion = proxima_coordenada_personaje;
	}

	if((
		(buscar_pared(nivel.paredes, nivel.tope_paredes, proxima_coordenada_sombra) == -1) &&
		esta_dentro_rango(proxima_coordenada_sombra, 0, MAX_FILAS - 1, 0, MAX_COLUMNAS - 1) &&
		(*sombra).esta_viva
	)) {
		(*sombra).posicion = proxima_coordenada_sombra;
	}
}


/*
	Pre: Recibimos al personaje por referencia
	Post: Le otorgamos una vida de ser posible, cumpliendo con tener los puntos y no superar
	el maximo de vidas. De lo contrario, no se suma nada ni resta nada
*/
void generar_vida(personaje_t* personaje) {
	if(((*personaje).puntos >= MIN_PUNTOS_VIDA) && ((*personaje).vida < MAX_VIDAS)) {
		(*personaje).vida++;
		(*personaje).puntos -= MIN_PUNTOS_VIDA;
	}
}

/* 
	Pre: Recibe por parametros dos referencias de tipo personaje_t y sombra_t, y una variable
	de tipo char
	Post: Si se valida el movimiento y dependiendo del mismo, el procedimiento llamara al 
	procedimiento mover_verticalmente() o mover_horizontalmente()
*/
void mover_personaje(juego_t* juego, char movimiento) {
	if(es_movimiento_valido(movimiento) && movimiento != VIDA) {
		mover_espacialemente(
			movimiento, 
			(*juego).niveles[(*juego).nivel_actual - 1], 
			&((*juego).personaje),
			&((*juego).sombra)
		);
	} else if(movimiento == VIDA) {
		generar_vida(&((*juego).personaje));
	}
}
