#include "colisiones.h"

/*
	Pre: Recibe un nivel_t y una coordenada
	Post Devuelve true si hay colision con al menos una pared, una herramienta o un obstaculo.
	En caso contrario devuelve false
*/
bool hay_colision(nivel_t nivel, coordenada_t posicion) {
	return (
		(buscar_elemento(nivel.obstaculos, nivel.tope_obstaculos, posicion) != -1) || 
		(buscar_elemento(nivel.herramientas, nivel.tope_herramientas, posicion) != -1) ||
		(buscar_pared(nivel.paredes, nivel.tope_paredes, posicion) != -1)
	);
}

/*
	Pre: -
	Post: Devuelve un numero entre 10 y 20
*/
int generar_puntos() {
	return (rand() % MAX_MONEDAS) + MIN_MONEDAS;
}

/* 
	Pre: Recibe una referencia del juego, un movimiento y la posicion donde hay un escalera
	Post: A partir del movimiento determina como se debe utilizar la escalera y en caso de
	utlizarse se elimina del vector
*/
void manejar_escalera(juego_t* juego, char movimiento, int posicion) {
	coordenada_t arriba = {(*juego).personaje.posicion.fila - 1, (*juego).personaje.posicion.col};
	coordenada_t derecha = {(*juego).personaje.posicion.fila, (*juego).personaje.posicion.col + 1};
	coordenada_t abajo = {(*juego).personaje.posicion.fila + 1, (*juego).personaje.posicion.col};
	coordenada_t izquierda = {(*juego).personaje.posicion.fila, (*juego).personaje.posicion.col - 1};
	bool se_movio = false;

	switch(movimiento) {
		case ARRIBA:
			if(
				(
					buscar_pared(
						(*juego).niveles[(*juego).nivel_actual - 1].paredes, 
						(*juego).niveles[(*juego).nivel_actual - 1].tope_paredes, 
						arriba
					) == -1) ||
				(
					buscar_escalera(
						(*juego).niveles[(*juego).nivel_actual - 1].herramientas,
						(*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas,
						arriba
					) != -1
				)
			) {
				(*juego).personaje.posicion.fila -= 1;
				se_movio = true;
			}
		break;
		case DERECHA:
			if(
				(
					buscar_pared(
						(*juego).niveles[(*juego).nivel_actual - 1].paredes, 
						(*juego).niveles[(*juego).nivel_actual - 1].tope_paredes, 
						derecha
					) == -1) ||
				(
					buscar_escalera(
						(*juego).niveles[(*juego).nivel_actual - 1].herramientas,
						(*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas,
						derecha
					) != -1
				)
			) {
				(*juego).personaje.posicion.col += 1;
				se_movio = true;
			}
		break;
		case ABAJO:
			if(
				(
					buscar_pared(
						(*juego).niveles[(*juego).nivel_actual - 1].paredes, 
						(*juego).niveles[(*juego).nivel_actual - 1].tope_paredes, 
						abajo
					) == -1) ||
				(
					buscar_escalera(
						(*juego).niveles[(*juego).nivel_actual - 1].herramientas,
						(*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas,
						abajo
					) != -1
				)
			) {
				(*juego).personaje.posicion.fila += 1;
				se_movio = true;
			}
		break;
		case IZQUIERDA:
			if(
				(
					buscar_pared(
						(*juego).niveles[(*juego).nivel_actual - 1].paredes, 
						(*juego).niveles[(*juego).nivel_actual - 1].tope_paredes, 
						izquierda
					) == -1) ||
				(
					buscar_escalera(
						(*juego).niveles[(*juego).nivel_actual - 1].herramientas,
						(*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas,
						izquierda
					) != -1
				)
			) {
				(*juego).personaje.posicion.col -= 1;
				se_movio = true;
			}
		break;
	}

	if(se_movio) {
		eliminar_elemento(
			(*juego).niveles[(*juego).nivel_actual - 1].herramientas, 
			&((*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas), 
			posicion
		);

		manejar_colisiones(juego, movimiento);
	}
}

/*
	Pre: Recibimos una referencia del juego y un movimiento
	Post: Si existe una colision entre el personaje una herramienta o un obstaculo 
	se maneja esa colision dependiendo que haya sido
*/
void manejar_colisones_personaje(juego_t* juego, char movimiento) {
	coordenada_t arranque_personaje; 
	coordenada_t arranque_sombra; 
	generar_coordenadas_personajes(*juego, &arranque_personaje, &arranque_sombra);

	int pos_buscado_herramientas = buscar_elemento(
		(*juego).niveles[(*juego).nivel_actual - 1].herramientas,
		(*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas,
		(*juego).personaje.posicion
	);

	int pos_buscado_obstaculos = buscar_elemento(
		(*juego).niveles[(*juego).nivel_actual - 1].obstaculos,
		(*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos,
		(*juego).personaje.posicion
	);

	if(
		coordenadas_iguales((*juego).personaje.posicion, (*juego).sombra.posicion) && 
		(!(*juego).sombra.esta_viva)
	) {
		(*juego).sombra.esta_viva = true;
		(*juego).personaje.puntos -= APAGAR_VELA;
	}

	if(pos_buscado_obstaculos != -1) {
		switch((*juego).niveles[(*juego).nivel_actual - 1].obstaculos[pos_buscado_obstaculos].tipo) {
			case POZOS:
				(*juego).personaje.vida--;
				(*juego).personaje.posicion = arranque_personaje;
				(*juego).sombra.posicion = arranque_sombra;
			break;
			case INTERRUPTORES:
				(*juego).personaje.interruptor_apretado = !(*juego).personaje.interruptor_apretado;
			break;
			case VELAS:
				eliminar_elemento(
					(*juego).niveles[(*juego).nivel_actual - 1].obstaculos, 
					&((*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos), 
					pos_buscado_obstaculos
				);
			break;
		}
	}

	if(pos_buscado_herramientas != -1) {
		switch((*juego).niveles[(*juego).nivel_actual - 1].herramientas[pos_buscado_herramientas].tipo) {
			case ESCALERAS:
				manejar_escalera(juego, movimiento, pos_buscado_herramientas);
			break;
			case LLAVE:
				(*juego).personaje.tiene_llave = true;
				eliminar_elemento(
					(*juego).niveles[(*juego).nivel_actual - 1].herramientas, 
					&((*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas), 
					pos_buscado_herramientas
				);
			break;
			case MONEDAS:
				(*juego).personaje.puntos += generar_puntos();
				eliminar_elemento(
					(*juego).niveles[(*juego).nivel_actual - 1].herramientas, 
					&((*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas), 
					pos_buscado_herramientas
				);
			break;
		}
	}
}

/*
	Pre: Recibimimos una referencia del juego, un vector de elementos y su tope
	Post: En caso de que la sombra este en el rango de la vela se muere :(
*/
void manejar_vela(juego_t* juego, elemento_t elementos[MAX_ELEMENTOS], int tope_elementos) {
	int i = 0;
	bool hay_vela = false;

	while(i < tope_elementos && !hay_vela) {
		bool hay_colision = esta_dentro_rango(
			(*juego).sombra.posicion,
			elementos[i].coordenada.fila - 1, elementos[i].coordenada.fila + 1,
			elementos[i].coordenada.col - 1, elementos[i].coordenada.col + 1
		);

		if(elementos[i].tipo == VELAS && hay_colision) {		
			(*juego).sombra.esta_viva = false;
			hay_vela = true;
		}
		i++;
	}
}

/*
	Pre: Recibimos una referencia del juego y un movimiento
	Post: Si existe una colision entre la sombra y una herramienta o un obstaculo 
	se maneja esa colision dependiendo que haya sido
*/
void manejar_colisones_sombra(juego_t* juego, char movimiento) {
	coordenada_t aux = (*juego).personaje.posicion;

	int pos_buscado_herramientas = buscar_elemento(
		(*juego).niveles[(*juego).nivel_actual - 1].herramientas,
		(*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas,
		(*juego).sombra.posicion
	);

	int pos_buscado_obstaculos = buscar_elemento(
		(*juego).niveles[(*juego).nivel_actual - 1].obstaculos,
		(*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos,
		(*juego).sombra.posicion
	);

	if(pos_buscado_obstaculos != -1) {
		char tipo = (*juego).niveles[(*juego).nivel_actual - 1].obstaculos[pos_buscado_obstaculos].tipo; 

		switch(tipo) {
			case PORTALES:
				(*juego).personaje.posicion = (*juego).sombra.posicion;
				(*juego).sombra.posicion = aux;
			break;
		}
	}

	if(pos_buscado_herramientas != -1) {
		switch((*juego).niveles[(*juego).nivel_actual - 1].herramientas[pos_buscado_herramientas].tipo) {
			case MONEDAS:
				(*juego).personaje.puntos += generar_puntos();
				eliminar_elemento(
					(*juego).niveles[(*juego).nivel_actual - 1].herramientas, 
					&((*juego).niveles[(*juego).nivel_actual - 1].tope_herramientas), 
					pos_buscado_herramientas
				);
			break;
		}
	}

	manejar_vela(
		juego, 
		(*juego).niveles[(*juego).nivel_actual - 1].obstaculos, 
		(*juego).niveles[(*juego).nivel_actual - 1].tope_obstaculos
	);
}

/*
	Pre: Recibimos una referencia del juego y el ultimo movimiento
	Post: Llamamamos a los procedimiento que manejan las colisiones del personaje y la 
	sombra
*/
void manejar_colisiones(juego_t* juego, char movimiento) {
	manejar_colisones_personaje(juego, movimiento);
	manejar_colisones_sombra(juego, movimiento);
}