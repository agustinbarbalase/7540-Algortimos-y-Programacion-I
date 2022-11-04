#include "personajes_y_niveles.h"

/* 
	Pre: Recibe por parametros una referencia a un struct tipo personaje_t
	y un struct de tipo coordenada_t
	Post: Asigna por referencia el struct coordenada_t
	a la componente posicion del personaje, siendo esta coordenada_t
*/
void inicializar_personaje(personaje_t* personaje, coordenada_t arranque_personaje) {
	(*personaje).posicion = arranque_personaje;
	(*personaje).vida = VIDAS_INICIALES;
	(*personaje).puntos = PUNTOS_INICIALES;
	(*personaje).tiene_llave = TIENE_LLAVE;
	(*personaje).interruptor_apretado = INTERRUPTOR_APRETADO;
}

/*
	Pre: Recibe por parametros una referencia a un struct tipo sombra_t y un struct
	de tipo coordenada_t
	Post: Asigna al struct sombra_t, una posicion.fila igual a la que se paso por
	parametro, pero una posicion.col diferente restando la maxima posicion horizontal
*/ 
void inicializar_sombra(sombra_t* sombra, coordenada_t arranque_sombra) {
	(*sombra).posicion = arranque_sombra;
	(*sombra).esta_viva = ESTA_VIVA;
}

/* 
	Pre: Recibir una variable tipo coordenada_t, correspondiente al personaje
	Post: Retornar dicha variable como una coordenada correspondiente a la sombra
*/
coordenada_t calcular_arranque_sombra(coordenada_t coordenada) {
	coordenada.col = (MAX_COLUMNAS - 1) - coordenada.col;
	return coordenada;
}

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
) {
	(*arranque_personaje) = coordenada_aleatoria(0, MAX_FILAS - 1, 0, MAX_COLUMNAS - 1);
	(*arranque_sombra) = calcular_arranque_sombra(*arranque_personaje);

	while(
		hay_colision(juego.niveles[juego.nivel_actual - 1], *arranque_personaje) || 
		hay_colision(juego.niveles[juego.nivel_actual - 1], *arranque_sombra)
	) {
		(*arranque_personaje) = coordenada_aleatoria(0, MAX_FILAS - 1, 0, MAX_COLUMNAS - 1);
		(*arranque_sombra) = calcular_arranque_sombra(*arranque_personaje);
	}
}

/*
	Pre: Recibimos un nivel por referencia, una cantidad y las coordenadas del personaje y su sombra
	Post: Agregamos las escaleras en posiciones validas y aleatorias, de acuerdo a la cantidad
*/
void inicializar_escaleras(
	nivel_t * nivel, int cantidad, 
	coordenada_t personaje, coordenada_t sombra
) {
	int i = 0;
	elemento_t nuevo_elemento;
	nuevo_elemento.tipo = ESCALERAS;

	while(i < cantidad) {
		int pos_pared = rand() % (*nivel).tope_paredes;
		
		if(
			esta_dentro_rango((*nivel).paredes[pos_pared], 1, MAX_FILAS - 2, 1, MAX_COLUMNAS - 2)
		) {
			nuevo_elemento.coordenada = (*nivel).paredes[pos_pared];
			agregar_elemento((*nivel).herramientas, &((*nivel).tope_herramientas), nuevo_elemento);
			i++;	
		}
	}
}

/*
	Pre: Recibimos un nivel por referencia, el tipo de elemento que vamos a agregar, 
	la cantidad de de dicho elemento, las coordenadas tanto del personaje como de la sombra. 
	Y por utlimo, un vector de elementos con su tope por referencia. Es importante que
	el tipo de elemento sea agregado al vector correcto, es decir, si agregamos una moneda, 
	debemos pasar el vector donde se guardan las herramientas y dicho tope
	Post: Agregamos la cantidad del elemento que pasamos por parametro dentro del vector,
	y aumentando su tope. Siempre corroborando que no se pise ningun obstaculo o herramienta
	previas, como asi tambien a las coordenadas de ambos personajes
*/
void agregar_elementos(
	nivel_t* nivel, char tipo, int cantidad, coordenada_t personaje, coordenada_t sombra,
	elemento_t elementos[MAX_ELEMENTOS], int* tope_elementos
) {
	int i = 0;
	elemento_t nuevo_elemento;
	nuevo_elemento.tipo = tipo;

	while(i < cantidad) {
		coordenada_t coordenada_elemento = coordenada_aleatoria(0, MAX_FILAS - 1, 0, MAX_COLUMNAS - 1);

		if(
			!hay_colision(*nivel, coordenada_elemento) && 
			!coordenadas_iguales(coordenada_elemento, personaje) && 
			!coordenadas_iguales(coordenada_elemento, sombra)
		) {
			nuevo_elemento.coordenada = coordenada_elemento;
			agregar_elemento(elementos, tope_elementos, nuevo_elemento);
			i++;
		}
	}

}	

/*
	Pre: Recibimos un nivel por referencia, un numero de nivel y las coordenadas del personaje 
	y su sombra
	Post: Generamos los obstaculos y herramientas de acuerdo al numero de nivel
*/
void inicializar_nivel(nivel_t* nivel, int numero_nivel, coordenada_t personaje, coordenada_t sombra) {
	(*nivel).tope_herramientas = 0;
	(*nivel).tope_obstaculos = 0;

	switch(numero_nivel) {
		case NIVEL_UNO:
			// Agregarmos obstaculos
			agregar_elementos(nivel, VELAS, CANT_VELAS_UNO, personaje, sombra, 
				(*nivel).obstaculos, &((*nivel).tope_obstaculos)
			);
			agregar_elementos(nivel, POZOS, CANT_POZOS_UNO, personaje, sombra, 
				(*nivel).obstaculos, &((*nivel).tope_obstaculos)
			);
			agregar_elementos(nivel, INTERRUPTORES, CANT_INTERRUPTORES_UNO, personaje, sombra, 
				(*nivel).obstaculos, &((*nivel).tope_obstaculos)
			);
			agregar_elementos(nivel, PORTALES, CANT_PORTALES_UNO, personaje, sombra, 
				(*nivel).obstaculos, &((*nivel).tope_obstaculos)
			);

			// Agregamos herramientas
			agregar_elementos(
				nivel, MONEDAS, CANT_MONEDAS_UNO, personaje, sombra, 
				(*nivel).herramientas, &((*nivel).tope_herramientas)
			);
			agregar_elementos(
				nivel, LLAVE, CANT_LLAVES_UNO, personaje, sombra, 
				(*nivel).herramientas, &((*nivel).tope_herramientas)
			);
			inicializar_escaleras(nivel, CANT_ESCALERAS_UNO, personaje, sombra);
		break;
		case NIVEL_DOS:
			agregar_elementos(nivel, VELAS, CANT_VELAS_DOS, personaje, sombra, 
				(*nivel).obstaculos, &((*nivel).tope_obstaculos)
			);
			agregar_elementos(nivel, POZOS, CANT_POZOS_DOS, personaje, sombra, 
				(*nivel).obstaculos, &((*nivel).tope_obstaculos)
			);
			agregar_elementos(nivel, INTERRUPTORES, CANT_INTERRUPTORES_DOS, personaje, sombra, 
				(*nivel).obstaculos, &((*nivel).tope_obstaculos)
			);
			agregar_elementos(nivel, PORTALES, CANT_PORTALES_DOS, personaje, sombra, 
				(*nivel).obstaculos, &((*nivel).tope_obstaculos)
			);

			agregar_elementos(nivel, MONEDAS, CANT_MONEDAS_DOS, personaje, sombra, 
				(*nivel).herramientas, &((*nivel).tope_herramientas)
			);
			agregar_elementos(nivel, LLAVE, CANT_LLAVES_DOS, personaje, sombra, 
				(*nivel).herramientas, &((*nivel).tope_herramientas)
			);
			inicializar_escaleras(nivel, CANT_ESCALERAS_DOS, personaje, sombra);
		break;
		case NIVEL_TRES:
			agregar_elementos(nivel, VELAS, CANT_VELAS_TRES, personaje, sombra, 
				(*nivel).obstaculos, &((*nivel).tope_obstaculos)
			);
			agregar_elementos(nivel, POZOS, CANT_POZOS_TRES, personaje, sombra, 
				(*nivel).obstaculos, &((*nivel).tope_obstaculos)
			);
			agregar_elementos(nivel, INTERRUPTORES, CANT_INTERRUPTORES_TRES, personaje, sombra, 
				(*nivel).obstaculos, &((*nivel).tope_obstaculos)
			);
			agregar_elementos(nivel, PORTALES, CANT_PORTALES_TRES, personaje, sombra, 
				(*nivel).obstaculos, &((*nivel).tope_obstaculos)
			);

			agregar_elementos(nivel, MONEDAS, CANT_MONEDAS_TRES, personaje, sombra, 
				(*nivel).herramientas, &((*nivel).tope_herramientas)
			);
			agregar_elementos(nivel, LLAVE, CANT_LLAVES_TRES, personaje, sombra, 
				(*nivel).herramientas, &((*nivel).tope_herramientas)
			);
			inicializar_escaleras(nivel, CANT_ESCALERAS_TRES, personaje, sombra);
		break;
	}

	agregar_elementos(nivel, PUERTA, CANT_PUERTAS, personaje, sombra, 
		(*nivel).herramientas, &((*nivel).tope_herramientas)
	);

	(*nivel).numero_nivel = numero_nivel;
}