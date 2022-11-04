#ifndef __LA_SOMBRA_DE_MAC__
#define __LA_SOMBRA_DE_MAC__

#include <stdbool.h>

#define MAX_FILAS 20
#define MAX_COLUMNAS 20
#define MAX_ELEMENTOS 500

#define ARRIBA 'W'
#define ABAJO 'S'
#define IZQUIERDA 'A'
#define DERECHA 'D'

typedef struct coordenada {
    int fila;
    int col;
} coordenada_t;

typedef struct elemento {
    coordenada_t posicion;
    char tipo;
} elemento_t;

typedef struct personaje {
    coordenada_t posicion;
    int vida;
    int puntos;
    bool tiene_llave;
    bool interruptor_apretado;
} personaje_t;

typedef struct sombra {
    coordenada_t posicion;
    bool esta_viva;
} sombra_t;

typedef struct juego {
    personaje_t personaje;
    sombra_t sombra;
    // se vienen cositas lindas.
} juego_t;

/*
* Función que recibe dos coordenadas, devuelve true si las
* coordenadas son iguales, sino false.
*/

bool coordenadas_iguales(coordenada_t a, coordenada_t b);

/*
* Procedimiento que dejará la estructura personaje_t en un
* estado válido para iniciar el juego.
* 'arranque_personaje' es un parámetro que representa la posición 
* en la arrancará el personaje.
*/

void inicializar_personaje(personaje_t* ref_personaje, coordenada_t arranque_personaje);

/*
* Procedimiento que dejará una estructura elemento_t que
* represente a la sombra, en un estado válido para iniciar el juego. 
* 'arranque_sombra' es un parámetro que representa la posición 
* en la arrancará la sombra.
*/

void inicializar_sombra(sombra_t* ref_sombra, coordenada_t arranque_sombra);

/*
* La función recibe un caracter y devuelve true
* si el movimiento recibido concuerda con la convención
* propuesta, sino false.
* -> W: Si el personaje debe moverse para la arriba. 
* -> A: Si el personaje debe moverse para la izquierda.
* -> S: Si el personaje debe moverse para la abajo.
* -> D: Si el personaje debe moverse para la derecha.
*/

bool es_movimiento_valido(char movimiento);

/*
* Procedimineto que se encargará de pedirle al usuario
* que ingrese un movimiento hasta que sea válido.
*/

void pedir_movimiento(char* ref_movimiento);

/*
* La función recibe una coordenada, devuelve true
* si la posición dentro de las dimensiones dadas, sino false.
* Una posición nunca podrá tener un valor negativo y no tendrá un 
* valor más alto que los máximos.
*/

bool esta_dentro_rango(coordenada_t posicion, int max_alto, int max_ancho);

/*
* El procedimiento recibe el personaje y la sombra por referencia y el movimiento,
* y según este último, los mueve acordemente.
* 
* El personaje se mueve de la forma:
* -> W: Si el personaje debe moverse para la arriba. 
* -> A: Si el personaje debe moverse para la izquierda.
* -> S: Si el personaje debe moverse para la abajo.
* -> D: Si el personaje debe moverse para la derecha.
*
* La sombra se mueve de igual forma para el eje vertical, pero
* para el eje horizontal se moverá de forma inversa:
*
* -> A: Si el personaje debe moverse para la derecha.
* -> D: Si el personaje debe moverse para la izquierda.
*/

void mover_personaje(personaje_t* ref_personaje, sombra_t* ref_sombra, char movimiento);

/*
* Función que dados una altura máxima y un ancho máximo
* devuelve una coordenada aleatoria. Una posición nunca podrá
* tener un valor negativo, ni ser mayor a sus máximos.
*/

coordenada_t coordenada_aleatoria(int max_alto, int max_ancho);

/*
* La función recibe un vector de elementos, su respectivo tope y una coordenada,
* devuelve la posición del elemento del vector, que coincida con la coordenada pasada 'posicion',
* si no se encuentra ningún elemento, se devolverá -1. 
*/

int buscar_elemento(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t posicion);

/*
* Procedimiento que recibe el juego e imprime 
* toda su información por pantalla.
*/

void imprimir_terreno(juego_t juego);

#endif