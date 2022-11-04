#ifndef __PROGRAMAS__
#define __PROGRAMAS__

#include <stdio.h>
#include <string.h>
#include "partidas.h"

// Definimos los tipos de programas
#define AGREGAR_PARTIDA  "agregar_partida"
#define ELIMINAR_PARTIDA "eliminar_partida"
#define ORDENAR_PARTIDA  "ordenar_partida"
#define CONFIG_JUEGO     "config_juego"

// Definimos los formatos de escritura
#define FORMATO_LECTURA_PARTIDA "%[^;];%i;%i;%i;%[^\n]\n"
#define FORMATO_LECTURA_CONFIG  "N%i_%[^=]=%i\n"
#define FORMATO_ESCRITURA       "%s;%i;%i;%i;%s\n"

#define ERROR -1
#define	EXITO  0

#define LEIDOS_PARTIDA 5
#define LEIDOS_CONFIG  3

#define ARCHIVO_SALIDA "_output.csv"
#define ARCHIVO_CONFIG "config.txt"

#define GANO    "Si"
#define NO_GANO "No"

// Definimos los nombres de los elementos del juego
#define NOMBRE_POZOS         "POZOS"						
#define NOMBRE_VELAS         "VELAS"						
#define NOMBRE_INTERRUPTORES "INTERRUPTORES"						
#define NOMBRE_PORTALES      "PORTALES"						
#define NOMBRE_MONEDAS       "MONEDAS"						
#define NOMBRE_ESCALERAS     "ESCALERAS"						
#define NOMBRE_LLAVES        "LLAVES"						

#define MAX_ELEMENTO 50
#define MAX_CONFIG 3

typedef struct config {
	int numero_nivel;
	int pozos;
	int velas;
	int interruptores;
	int portales;
	int monedas;
	int escaleras;
	int llaves;
} config_t;

/*
	Pre: Recibimos un nombre de un archivo para leer y que queremos que sea
	manipulado (Ese archivo tiene que tener un formato concreto y ser .csv)
	Post: Con la informacion brindada por el usuario, escribimos esa informacion
	en el archivo pasado por parametro
*/
int agregar_partida(char nombre_archivo[]);

/*
	Pre: Recibimos un nombre de un archivo para leer y que queremos que sea
	manipulado (Ese archivo tiene que tener un formato concreto y ser .csv). 
	Junto con un nombre de un jugador que hay en ese archivo
	Post: Eliminamos del archivo pasado por parametro, una sola partida del jugador
	pasado por parametro
*/
int eliminar_partida(char nombre_archivo[], char nombre_jugador[]);

/*
	Pre: Recibimos un nombre de un archivo para leer y que queremos que sea
	manipulado (Ese archivo tiene que tener un formato concreto y ser .csv)
	Post: Ordenamos las partidas, de ese archivo, por jugador
*/
int ordenar_partidas(char nombre_archivo[]);

/*
	Pre: Recibimos configuraciones que no esten vacias, sino con valores por defecto.
	Tambien necesitamos que exista un archivo llamado "config.txt" para ser leido, y 
	con un formato concreto
	Post: Leemos las configuraciones que hay en el archivo y las aplicamos sobre las
	configuraciones pasadas por parametro
*/
int config_juego(config_t configuraciones[MAX_CONFIG]);

#endif