#include "la_sombra_de_mac.h"
#include "coordenadas_y_movimiento.h"
#include "personajes_y_niveles.h"
#include "colisiones.h"
#include "interfaces.h"
#include "utiles.h"
#include "constantes.h"
#include <stdlib.h>

/*
	Pre: Recibimos el juego en un momento concreto
	Post: Imprimimos por pantalla el terreno de juego y la informacion de los
	personajes
*/
void imprimir_terreno(juego_t juego) {
	imprimir_datos_personajes(juego.personaje, juego.sombra);
	imprimir_area_de_juego(juego);
}

/*
	Pre: Recibimos una referencia del juego de forma vacia
	Post: Armamos el juego, llenandolo de las paredes, los personajes y los elementos.
	Para los tres niveles
*/
void inicializar_juego(juego_t* juego, config_t configuraciones[MAX_CONFIG]) {
	cargar_mapas();

	int i = 0;
    (*juego).nivel_actual = 1;

	while(i < MAX_NIVELES) {
		coordenada_t arranque_personaje = {0, 0};
		coordenada_t arranque_sombra = {0, 0};

		obtener_mapa((*juego).niveles[i].paredes, &((*juego).niveles[i].tope_paredes));

    	if(i == 0) {
			generar_coordenadas_personajes(*juego, &arranque_personaje, &arranque_sombra);

		    inicializar_personaje(&((*juego).personaje), arranque_personaje);
		    inicializar_sombra(&((*juego).sombra), arranque_sombra);
    	}
		
		inicializar_nivel(&((*juego).niveles[i]), i + 1, arranque_personaje, arranque_sombra, configuraciones);
		i++; 	
	}
}

/*
	Pre: Recibimos un estado del juego en un momento determinado
	Post: Retornamos el estado del nivel actual, bajo las siguientes condiciones:
	- Si ambos personajes esta a una distancia manhattan de 1 o menos respecto a la puerta,
	la sombra esta viva y el personaje tiene al menos una vida entonces:
		- Si el nivel actual es el 1 entonces retornamos un ESTADO_GANADO
		- Si el nivel actual es 2 o mas y el personaje tiene la llave entonces 
		retornamos un ESTADO_GANADO
	- De lo contrario, entonces retornamos un ESTADO_JUGANDO
*/
int estado_nivel(juego_t juego) {
	int pos_puerta = buscar_puerta(
		juego.niveles[juego.nivel_actual - 1].herramientas, 
		juego.niveles[juego.nivel_actual - 1].tope_herramientas
	);
	
	if(
		distancia_manhattan(
			juego.personaje.posicion, 
			juego.niveles[juego.nivel_actual - 1].herramientas[pos_puerta].coordenada
		) <= 1 && 
		distancia_manhattan(
			juego.sombra.posicion, 
			juego.niveles[juego.nivel_actual - 1].herramientas[pos_puerta].coordenada
		) <= 1 &&
		juego.sombra.esta_viva &&
		juego.personaje.vida > 0
	) {
		if(juego.nivel_actual < 2 || (juego.nivel_actual >= 2 && juego.personaje.tiene_llave)) {
			return ESTADO_GANADO;
		}
	}
	
	return ESTADO_JUGANDO;
}

/*
	Pre: Recibimos un estado del juego en un momento determinado
	Post: Retornamos tres estados diferentes bajo ciertas condiciones:
	- Si el personaje tiene menos 1 una vida entonces retornamos un ESTADO_PERDIDO
	- Si el estado del nivel actual es 1 y el nivel actual es el ultimo (3) entonces 
	retornamos un ESTADO_GANADO
	- De lo contrario, entonces retornamos ESTADO_JUGANDO
*/
int estado_juego(juego_t juego) {
	if(juego.personaje.vida < 1) {
		return ESTADO_PERDIDO;
	} else if(estado_nivel(juego) == 1 && juego.nivel_actual == 3) {
		return ESTADO_GANADO;
	} else {
		return ESTADO_JUGANDO;
	}
}

/*
	Pre: Recibimos el juego por referencia
	Post: Llamamos al procedimiento que le pide un movimiento al jugador, dado ese movimiento
	movemos a los personajes y manejamos las colisiones en base a ese movimiento
*/
void realizar_jugada(juego_t* juego) {
	char movimiento = ' ';

	pedir_movimiento(&movimiento);
	mover_personaje(juego, movimiento);
	manejar_colisiones(juego, movimiento);
}
