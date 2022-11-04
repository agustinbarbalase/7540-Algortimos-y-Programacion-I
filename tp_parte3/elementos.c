#include "elementos.h"

/* 
	Pre: Recibe un vector de elemento_t, un int y un struct coordenada_t
	Post: Retorna la posicion dentro del vector elemento_t, si cuyo elemento_t
	comparte componente posicion con la coordenada_t pasada por parametro. En caso contrario
	retorna -1 
*/
int buscar_elemento(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t posicion) {
	int i = 0;
	int pos_encontrada = -1;
	
	while((pos_encontrada == -1) && i < tope) {;
		if(coordenadas_iguales(elementos[i].coordenada, posicion)) {
			pos_encontrada = i;
		}
		i++;
	}

	return pos_encontrada;
}

/* 
	Pre: Recibe un vector de paredes con su tope y una coordenada_t
	Post: Devuelve la posicion del vector en donde la posicion pasa como parametro coicide 
	con una que conicida en el vector, en caso contrario devuelve -1
*/
int buscar_pared(coordenada_t paredes[MAX_PAREDES], int tope_paredes, coordenada_t posicion) {
	int pos_encontrada = -1;

	int i = 0;

	while((i < tope_paredes) && (pos_encontrada == -1)) {
		if(coordenadas_iguales(paredes[i], posicion)) {
			pos_encontrada = i;
		}
		i++;
	}

	return pos_encontrada;
}

/*
	Pre: Recibe un vector de tipo elemento_t con su tope
	Post: Devuelve la posicion donde esta la puerta
*/
int buscar_puerta(elemento_t elementos[MAX_ELEMENTOS], int tope) {
	int i = 0;
	int pos_puerta = -1;

	while((i < tope) && (pos_puerta == -1)) {
		if(elementos[i].tipo == PUERTA) {
			pos_puerta = i;
		}
		i++;
	}

	return pos_puerta;
}

/*
	Pre: Recibe un vector de tipo elemento_t con su tope y una posicion
	Post: Devuelve la posicion donde haya una escalera en la posicion que pasamos por 
	parametro, en caso de que no haya devolvemos -1
*/
int buscar_escalera(elemento_t elementos[MAX_ELEMENTOS], int tope, coordenada_t coordenada) {
	int i = 0;
	int pos_encontrada = -1;

	while((i < tope) && (pos_encontrada == -1)) {
		if(coordenadas_iguales(elementos[i].coordenada, coordenada) && elementos[i].tipo == ESCALERAS) {
			pos_encontrada = i;
		}
		i++;
	}

	return pos_encontrada;
}

/* 
	Pre: Recibe un vector de elemento_t con su tope por referencia y un elemento_t
	Post: Agrega un elemento en el vector y aumenta su tope
*/
void agregar_elemento(elemento_t elementos[MAX_ELEMENTOS], int* tope, elemento_t elemento) {
	elementos[*tope] = elemento;
	(*tope)++;
}

/* 
	Pre: Recibe un vector de elementos con su tope por referencia y un int
	Post: Elimina un elemento en el vector, si es que pos_buscado es diferente a -1. Y reduce
	su tope 
*/
void eliminar_elemento(elemento_t elementos[MAX_ELEMENTOS], int* tope, int pos_buscado) {
	if(pos_buscado == -1) {
		return;
	}

	elementos[pos_buscado].tipo = elementos[*tope - 1].tipo;
	elementos[pos_buscado].coordenada = elementos[*tope - 1].coordenada;
	(*tope)--;
}
