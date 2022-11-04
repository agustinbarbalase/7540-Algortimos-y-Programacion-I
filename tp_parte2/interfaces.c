#include "interfaces.h"

/*
	Pre: -
	Post: Muestra por pantalla la presentación 
*/
void imprimir_presentacion() {
	printf(" \
		\f|=================================================|\n \
		|                /                                |\n \
		|    #((########(########                         |\n \
		|  (######################(                       |\n \
		| (#########################                      |\n \
		| ##########################*                     |\n \
		| #########################(,    /(((((((((,      |\n \
		| ##########(#,,,###########   ((    (.  #((/*    |\n \
		| ###(#*# (&,,,,,,,#&.#/#(##  (/(    # (  /(((/   |\n \
		| *##,,    *,,,,,,,    ,,,## /((((/(((((#((((((   |\n \
		|   ##,,,,,,,,#,,,,,,,,,,#*  /(((((((((((((((((,  |\n \
		|     /##(#(#,,.#####(#(     /(((((((((((((((((,  |\n \
		|         (#*////            *//(((((((((((((((*  |\n \
		|        #(((&(((#           ,/((((((((((((((/(/  |\n \
		|        *#((/(((&.          ,(((((((((((((((((/  |\n \
		|        (.  ,((((.          .(((((((((((((((((/  |\n \
		|         /####&(#*           //(((((((/((((((((  |\n \
		|          ,,,,,*,,           /(((((((((((((((((  |\n \
		|        ,*,,,,,,*,,          /(((((((((((((((((  |\n \
		|        /( ##&&&&( .         (((/(((///////////  |\n \
		|=================================================|\n \
	");
	printf("\n");
}

/*
	Pre: Recibimos al personaje y su sombra
	Post: Imprimimos por pantalla su informacion
*/
void imprimir_datos_personajes(personaje_t personaje, sombra_t sombra) {
	printf(" \
		========== MAC ==========|========= BLOO ==========\n \
		Pos:            (%i ,%i )|Pos:            (%i ,%i )\n \
		Vidas:                 %i|Esta Viva:             %i\n \
		Puntos:                %i|                         \n \
		Llave:                 %i|                         \n \
		Interruptor:           %i|	                       \n \
		=========================|=========================\n \
	\n", 
		personaje.posicion.fila, personaje.posicion.col, 
		sombra.posicion.fila, sombra.posicion.col, 
		personaje.vida, sombra.esta_viva, personaje.puntos, 
		personaje.tiene_llave, personaje.interruptor_apretado);
}

/*
	Pre: Recibe un tipo de elemento a partir de sus convenciones
	Post: Imprime por pantalla el emoji asociado a esa convencion
*/
void imprimir_emoji(char tipo) {
	switch(tipo) {
		case MAC:
			printf("%s", EMOJI_MAC);
		break;
		case BLOO:
			printf("%s", EMOJI_BLOO);
		break;
		case PUERTA:
			printf("%s", EMOJI_PUERTA);
		break;
		case ESCALERAS:
			printf("%s", EMOJI_ESCALERA);
		break;
		case LLAVE:
			printf("%s", EMOJI_LLAVE);
		break;
		case MONEDAS:
			printf("%s", EMOJI_MONEDA);
		break;
		case POZOS:
			printf("%s", EMOJI_POZOS);
		break;
		case INTERRUPTORES:
			printf("%s", EMOJI_INTERRUPTOR);
		break;
		case PORTALES:
			printf("%s ", EMOJI_PORTAL);
		break;
		case VELAS:
			printf("%s ", EMOJI_VELA);
		break;
		case PARED:
			printf("%s", EMOJI_PARED);
		break;
		case SUELO:
			printf("%s", EMOJI_SUELO);
		break;
	}
}

/*
	Pre: Recibimos el juego y una coordenada
	Post: Retornamos el caracter asociado a la colision, ya se el personaje, la sombra
	un elemento o una pared. En caso contrario, retornamos el caracter asociado al suelo
*/
char detectar_colision(juego_t juego, coordenada_t coordenada_actual) {
	nivel_t nivel_actual = juego.niveles[juego.nivel_actual - 1];

	int pos_obstaculo = buscar_elemento(
		nivel_actual.obstaculos, 
		nivel_actual.tope_obstaculos,
		coordenada_actual
	);
	int pos_herramientas = buscar_elemento(
		nivel_actual.herramientas, 
		nivel_actual.tope_herramientas,
		coordenada_actual
	);
	
	if(coordenadas_iguales(juego.personaje.posicion, coordenada_actual)){
		return MAC;
	} else if(coordenadas_iguales(juego.sombra.posicion, coordenada_actual)) {
		return BLOO;
	} else if(pos_obstaculo != -1) {
		return nivel_actual.obstaculos[pos_obstaculo].tipo;
	} else if(pos_herramientas != -1) {
		return nivel_actual.herramientas[pos_herramientas].tipo;
	} else if(
		buscar_pared(nivel_actual.paredes, nivel_actual.tope_paredes, coordenada_actual) != -1
	) {
		return PARED;
	} else {
		return SUELO;
	}	
}

/* 
	Pre: Recibimos el juego
	Post: Imprimimos por pantalla, el terreno de juego. Eso incluye las paredes, los personajes,
	las herramientas y los obstaculos
*/
void imprimir_area_de_juego(juego_t juego) {
	coordenada_t coordenada_actual;

	for(int i = 0; i < MAX_FILAS; i++) {
		for(int j = 0; j < MAX_COLUMNAS; j++) {
			coordenada_actual.fila = i;
			coordenada_actual.col = j;

			imprimir_emoji(
				detectar_colision(juego, coordenada_actual)
			);
		}
		printf("\n");
	}
}