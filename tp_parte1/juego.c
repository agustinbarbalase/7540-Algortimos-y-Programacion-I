#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "la_sombra_de_mac.h"

/* 
	Función que retorna true o false, si dos entero son iguales o no
	Pre: Dos variables de tipo int
	Post: Retorna true si ambas variables son iguales, o false
*/

bool espero_int(int a, int b) {
  return a == b;
}

/* 
	Función que retorna true o false, si dos booleanos son iguales o no
	Pre: Dos variables de tipo bool
	Post: Retorna true si ambas variables son iguales, o false
*/

bool espero_bool(bool a, bool b) {
  return a == b;
}

/* 
	Procedimiento que imprimie el resultado de los tests
	Pre: Una variable de tipo bool
	Post: Imprime por pantalla:
	- Si resultado_test es true: "Test pasó"
	- Si resultado_test es false: "Test falló"
*/

void muestro_resultado(bool resultado_test) {
  if(!resultado_test) {
    printf("- Test falló\n");
  } else {
    printf("- Test pasó\n");
  }
}

/* 
	Procedimiento que prueba a la funcion coordenadas_iguales()
	Post:
	- Si funciona, imprimira: "Test pasó", por cada prueba
	- Si no funciona, imprimira: "Test falló", por cada prueba
*/

void probar_coordenadas_iguales() {
  printf("Test: coordenadas_iguales()\n");

  coordenada_t primera_coordenada;
  coordenada_t segunda_coordenada;

  primera_coordenada.fila = 3;
  primera_coordenada.col = 2;
  segunda_coordenada.fila = 3;
  segunda_coordenada.col = 2;

  muestro_resultado(espero_bool(coordenadas_iguales(primera_coordenada, segunda_coordenada), true));

  primera_coordenada.fila = 1;
  primera_coordenada.col = 2;
  segunda_coordenada.fila = 3;
  segunda_coordenada.col = 4;

  muestro_resultado(espero_bool(coordenadas_iguales(primera_coordenada, segunda_coordenada), false));
}

/* 
	Procedimiento que prueba a la funcion esta_dentro_rango()
	Post:
	- Si funciona, imprimira: "Test pasó", por cada prueba
	- Si no funciona, imprimira: "Test falló", por cada prueba
*/

void probar_esta_dentro_rango() {
  printf("Test: esta_dentro_rango()\n");

  coordenada_t coordenada_personaje ;
  coordenada_personaje.fila = -1;
  coordenada_personaje.col = 31;

  muestro_resultado(espero_bool(esta_dentro_rango(coordenada_personaje, MAX_FILAS, MAX_COLUMNAS), false));

  coordenada_personaje.fila = 1;
  coordenada_personaje.col = 1;

  muestro_resultado(espero_bool(esta_dentro_rango(coordenada_personaje, MAX_FILAS, MAX_COLUMNAS), true));
}

/* 
	Procedimiento que prueba a la funcion es_movimiento_valido()
	Post:
	- Si funciona, imprimira: "Test pasó", por cada prueba
	- Si no funciona, imprimira: "Test falló", por cada prueba
*/

void probar_es_movimiento_valido() {
  printf("Test: es_movimiento_valido()\n");

  char movimiento = 'W';
  muestro_resultado(espero_bool(es_movimiento_valido(movimiento), true));

  movimiento = 'F';
  muestro_resultado(espero_bool(es_movimiento_valido(movimiento), false));
}

/* 
	Procedimiento que prueba a la funcion buscar_elemento()
	Post:
	- Si funciona, imprimira: "Test pasó", por cada prueba
	- Si no funciona, imprimira: "Test falló", por cada prueba
*/

void probar_buscar_elemento() {
  printf("Test: buscar_elemento()\n");

  elemento_t elementos [3];
  elementos[0].posicion.fila = 1;
  elementos[0].posicion.col = 1;
  elementos[0].tipo = 'A';
  
  elementos[1].posicion.fila = 2;
  elementos[1].posicion.col = 2;
  elementos[1].tipo = 'A';
  
  elementos[2].posicion.fila = 3;
  elementos[2].posicion.col = 3;
  elementos[2].tipo = 'A';
  int tope = 3;
  coordenada_t pos_buscado = {5, 0};

  muestro_resultado(espero_int(buscar_elemento(elementos, tope, pos_buscado), -1));

  elementos[0].posicion.fila = 1;
  elementos[0].posicion.col = 1;
  elementos[0].tipo = 'A';

  elementos[1].posicion.fila = 2;
  elementos[1].posicion.col = 2;
  elementos[1].tipo = 'A';

  elementos[2].posicion.fila = 3;
  elementos[2].posicion.col = 3;
  elementos[2].tipo = 'A';

  tope = 3;

  pos_buscado.fila = 2;
  pos_buscado.col = 2;

  muestro_resultado(espero_int(buscar_elemento(elementos, tope, pos_buscado), 1));
}

/* 
	Procedimiento para comprobar que ciertas funcionalidades del juego, funcionan correctamente
	Post: Imprime por pantalla el resultado de las pruebas. 
*/	

void probar_funcionalidades() {
	// Probamos algunas funcionalidades
	probar_coordenadas_iguales();
	probar_esta_dentro_rango();
	probar_es_movimiento_valido();
	probar_buscar_elemento();
	printf("\n");
}

/*
	Procedimiento que imprime por pantalla una presentación
	Post: Muestra por pantalla la presentación 
*/

void imprimir_presentacion() {
	printf(" \
		|=================================================|\n \
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

int main() {
	srand ((unsigned)time(NULL));
	
	system("clear");

	imprimir_presentacion();
	probar_funcionalidades();

	// Definimos las variables mas importantes para el juego
	coordenada_t coordenada_inicial = coordenada_aleatoria(MAX_FILAS, MAX_COLUMNAS);
	coordenada_t coordenada_sombra;

	coordenada_sombra.fila = coordenada_inicial.fila;
	coordenada_sombra.col = (MAX_COLUMNAS - 1) - coordenada_inicial.col;

	juego_t juego;
	char movimiento;

	// Asignamos las posiciones a los personajes
	inicializar_personaje(&juego.personaje, coordenada_inicial);
	inicializar_sombra(&juego.sombra, coordenada_sombra);

	// Pedimos movimientos e imprimimos dichos cambios
	while(true) {
		imprimir_terreno(juego);
		pedir_movimiento(&movimiento);
		mover_personaje(&juego.personaje, &juego.sombra, movimiento);
		system("clear");
	}

	return 0;
}
