#include "partidas.h"

/*
	Pre: Recibimos un archivo en modo leer y un struct partida_t vacio
	Post: Escribimos en el struct la informacion del archivo y retornamos
	la cantidad de parametros que leyo fscanf() 
*/
int leer_archivo(FILE* arch, partida_t* partida) {
	int leidos;
	char gano[MAX_GANO];

	leidos = fscanf(arch, FORMATO_LECTURA_PARTIDA, 
		(*partida).jugador,
		&((*partida).nivel_llegado),
		&((*partida).puntos),
		&((*partida).vidas_restantes),
		gano
	);
	(*partida).gano = strcmp(gano, GANO) == 0;

	return leidos;
}

/*
	Pre: Recibimos un archivo en modo escribir y un struct partida_t no vacio
	Post: Escribimos en el archivo la informacion del struct
*/
void escribir_archivo(FILE* arch, partida_t partida) {
	char gano[MAX_GANO];

	if(partida.gano) {
		strcpy(gano, GANO);
	} else {
		strcpy(gano, NO_GANO);
	}

	fprintf(arch, FORMATO_ESCRITURA,
		partida.jugador,
		partida.nivel_llegado,
		partida.puntos,
		partida.vidas_restantes,
		gano
	);
}

/*
	Pre: Recibimos dos archivos uno en modo leer y el otro en modo escribir. Y struct
	partida_t no vacio
	Post: Agregamos en el archivo la partida respetando el orden alfabetico y pre establecido
	del archivo
*/
void agregar_ordenandamente(FILE* partida_arch, FILE* partida_aux, partida_t nueva_partida) {
	bool insertado = false;
	partida_t partida;
	int leidos;

	leidos = leer_archivo(partida_arch, &partida);
	while(leidos == LEIDOS_PARTIDA) {
		if(strcmp(partida.jugador, nueva_partida.jugador) > 0 && !insertado) {
			escribir_archivo(partida_aux, nueva_partida);
			insertado = true;
		}
		escribir_archivo(partida_aux, partida);
		leidos = leer_archivo(partida_arch, &partida);
	};
}

/*
	Pre: Recibimos dos archivos uno en modo leer y el otro en modo escribir. Y un nombre
	de jugador, que puede estar o no en el archivo leido
	Post: Eliminamos del archivo leido, el jugador que pasamos por parametro
*/
void eliminar_ordenadamente(FILE* partida_arch, FILE* partida_aux, char nombre_jugador[]) {
	bool eliminada = false;
	partida_t partida;
	int leidos;

	leidos = leer_archivo(partida_arch, &partida);
	while(leidos == LEIDOS_PARTIDA) {
		if(
			strcmp(nombre_jugador, partida.jugador) != 0 || 
			(strcmp(nombre_jugador, partida.jugador) == 0 && eliminada)
		) {
			escribir_archivo(partida_aux, partida);
		} else {
			eliminada = true;
		}

		leidos = leer_archivo(partida_arch, &partida);
	}
}

/*
	Pre: Recibimos dos archivos, uno en modo leer y el otro en modo escribir
	Post: Leemos del archivo para leer, las partidas y las guardamos en un vector
	para ordenarlas, y esos elementos del vector los escribimos en el otro archivo
*/
void ordenar_por_jugador(FILE* partida_arch, FILE* partida_aux) {
	partida_t partidas[MAX_PARTIDA];
	int tope = 0;
	int leidos;

	leidos = leer_archivo(partida_arch, &(partidas[tope]));
	while(leidos == LEIDOS_PARTIDA) {
		tope++;
		leidos = leer_archivo(partida_arch, &(partidas[tope]));
	}

	int pos_minimo;

	/*
	 	A medida que recorremos el vector, lo vamos escribiendo
	 	de forma ordenanda con un algoritmo de insercion
	*/
	for(int i = 0; i < tope; i++) {
		pos_minimo = i;
		for(int j = i + 1; j <= tope - 1; j++) {
			if(strcmp(partidas[pos_minimo].jugador, partidas[j].jugador) > 0) {
				pos_minimo = j;
			}
		}
		escribir_archivo(partida_aux, partidas[pos_minimo]);
		partidas[pos_minimo] = partidas[i];
	}
}
