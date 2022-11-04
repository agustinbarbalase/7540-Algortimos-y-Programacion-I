#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "la_sombra_de_mac.h"
#include "_tests.h"
#include "interfaces.h"
#include "utiles.h"
#include "constantes.h"

/*
	Pre: Recibimos un modo
	Post: Retornamos un true si el modo es:
	- Jugar
	- Testear
	- Salir
	De lo contrario, retoramos false
*/
bool es_modo_inicio_valido(char modo) {
	switch(modo) {
		case JUGAR:
			return true;
		break;
		case TEST:
			return true;
		break;
		case SALIR:
			return true;
		break;
		default:
			return false;
	}
}

/*
	Pre: Recibimos una referecia de un modo, suponiendo que esta vacio
	Post: Le pedimos al jugador que ingrese un modo que puede ser:
	- Jugar
	- Testear
	- Salir
	De lo contrario, imprimimos por pantalla un mensaje hasta que el usuario
	ingrese un modo valido
*/
void pedir_modo_inicio(char* modo) {
	do {
		printf("Jugar (J), Testear (T), Salir (Q)\n");
		printf("Ingresar modo: ");
		scanf(" %c", modo);
		system("clear");
		if(!es_modo_inicio_valido(*modo)) {
			printf("¡Modo Invalido!\n");
		}
	} while(!es_modo_inicio_valido(*modo));
}

/*
	Pre: Recibimos el juego por referencia para poder modificarlo, suponiendo
	que el ultimo estado del nivel antes de llamar a esta funcion fue ESTADO_PASADO
	Post: Modificamos el nivel aumentandolo y generamos nuevas posiciones para los personajes
	en el siguiente nivel
*/
void pasar_de_nivel(juego_t* juego) {
	coordenada_t arranque_personaje;
	coordenada_t arranque_sombra;

	(*juego).nivel_actual++;
	(*juego).personaje.interruptor_apretado = false;

	generar_coordenadas_personajes(*juego, &arranque_personaje, &arranque_sombra);

	(*juego).personaje.posicion = arranque_personaje;
	(*juego).sombra.posicion = arranque_sombra;
}

/*
	Pre: Recibimos el juego por referencia, antes de arrancar
	Post: Modificamos el juego a medida que el jugador interactua y retornamos el estado 
	del juego cuando gana o cuando pierde
*/
int arrancar_partida(juego_t* juego) {
	while(estado_juego(*juego) == 0) {
		if(estado_nivel(*juego) == 1) {
			pasar_de_nivel(juego);
		}
		imprimir_terreno(*juego);
		realizar_jugada(juego);
		system("clear");
	}

	if(estado_juego(*juego) == 1) {
		printf("Ganaste\n");
	} else if(estado_juego(*juego) == -1) {
		printf("Perdiste\n");
	}

	return estado_juego(*juego);
}


/* 
	Pre: -
	Post: Arrancar el juego pidiendo un modo, que puede ser jugar (J), testear (T) o salir (Q)
*/
void arrancar_juego() {
	char modo = ' ';
	int estado_juego = -1;

	do {
		pedir_modo_inicio(&modo);
		if(modo == JUGAR) {	
			do {
				juego_t juego;
				inicializar_juego(&juego);
				estado_juego = arrancar_partida(&juego);
			} while(estado_juego != ESTADO_PERDIDO && estado_juego != ESTADO_GANADO);
		} else if(modo == TEST) {
			probar_funcionalidades();
		}
	} while(modo != SALIR);
}

int main() {
	// Inicializamos funciones de arranque y limpiamos la pantalla
	srand ((unsigned)time(NULL));
	system("clear");

	imprimir_presentacion();
	arrancar_juego();
	return 0;
}
