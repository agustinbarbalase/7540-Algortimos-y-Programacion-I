#include "programas.h"

/*
	Pre: Recibimos una referencia vacia de una partida
	Post: Le pedimos al usuario que ingrese los valores correspondientes a la
	partida
*/
void pedir_partida(partida_t* nueva_partida) {
	char gano[MAX_GANO];

	printf("Nombre del jugador: ");
	scanf("%s", (*nueva_partida).jugador);	
	printf("Numero del nivel llegado: ");
	scanf("%i", &((*nueva_partida).nivel_llegado));
	printf("Cantidad de puntos: ");
	scanf("%i", &((*nueva_partida).puntos));
	printf("Vidas restantes: ");
	scanf("%i", &((*nueva_partida).vidas_restantes));	
	
	do {
		printf("Gano (Si) o (No): ");
		scanf("%s", gano);
		if(strcmp(gano, GANO) != 0 && strcmp(gano, NO_GANO) != 0) {
			printf("Opcion invalida\n");
		}
	} while(strcmp(gano, GANO) != 0 && strcmp(gano, NO_GANO) != 0);

	(*nueva_partida).gano = strcmp(gano, GANO) == 0;
}

/*
	Pre: Recibimos un nombre de un archivo para leer y que queremos que sea
	manipulado (Ese archivo tiene que tener un formato concreto y ser .csv)
	Post: Con la informacion brindada por el usuario, escribimos esa informacion
	en el archivo pasado por parametro
*/
int agregar_partida(char nombre_archivo[]) {
	FILE* arch = fopen(nombre_archivo, "r");
	if(!arch) {
		perror("Error to open file: arch");
		return ERROR;
	}

	FILE* aux = fopen(ARCHIVO_SALIDA, "w");
	if(!aux) {
		perror("Error to open file: aux");
		return ERROR;
	}

	partida_t nueva_partida;
	
	pedir_partida(&nueva_partida);
	agregar_ordenandamente(arch, aux, nueva_partida);

	fclose(arch);
	fclose(aux);
	rename(ARCHIVO_SALIDA, nombre_archivo);

	return EXITO;
}

/*
	Pre: Recibimos un nombre de un archivo para leer y que queremos que sea
	manipulado (Ese archivo tiene que tener un formato concreto y ser .csv). 
	Junto con un nombre de un jugador que hay en ese archivo
	Post: Eliminamos del archivo pasado por parametro, una sola partida del jugador
	pasado por parametro
*/
int eliminar_partida(char nombre_archivo[], char nombre_jugador[]) {
	for(int i = 0; i < strlen(nombre_jugador); i++) {
		if(nombre_jugador[i] == '_') {
			nombre_jugador[i] = ' ';
		}
	}
	
	FILE* arch = fopen(nombre_archivo, "r");
	if(!arch) {
		perror("Error to open file: arch");
		return ERROR;
	}

	FILE* aux = fopen(ARCHIVO_SALIDA, "w");
	if(!aux) {
		perror("Error to open file: aux");
		return ERROR;
	}

	eliminar_ordenadamente(arch, aux, nombre_jugador);	

	fclose(arch);
	fclose(aux);
	rename(ARCHIVO_SALIDA, nombre_archivo);

	return EXITO;
}

/*
	Pre: Recibimos un nombre de un archivo para leer y que queremos que sea
	manipulado (Ese archivo tiene que tener un formato concreto y ser .csv)
	Post: Ordenamos las partidas, de ese archivo, por jugador
*/
int ordenar_partidas(char nombre_archivo[]) {
	FILE* arch = fopen(nombre_archivo, "r");
	if(!arch) {
		perror("Error to open file: arch");
		return ERROR;
	}

	FILE* aux = fopen(ARCHIVO_SALIDA, "w");
	if(!aux) {
		perror("Error to open file: aux");
	}

	ordenar_por_jugador(arch, aux);

	fclose(arch);
	fclose(aux);
	rename(ARCHIVO_SALIDA, nombre_archivo);

	return EXITO;
}

/*
	Pre: Recibimos una configuracion por referencia (vacia o no), 
	una cantidad y un nombre de elemento. Que en principio dicho elemento exista
	Post: Aplicamos la cantidad dentro de la configuracion, en base al elemento pasado por
	parametro
*/
void establecer_cantidad_elemento(config_t* configuracion, int cantidad, char nombre_elemento[MAX_ELEMENTO]) {
	if(strcmp(NOMBRE_POZOS, nombre_elemento) == 0) {
		(*configuracion).pozos = cantidad;
	} else if(strcmp(NOMBRE_VELAS, nombre_elemento) == 0) {
		(*configuracion).velas = cantidad;
	} else if(strcmp(NOMBRE_INTERRUPTORES, nombre_elemento) == 0) {
		(*configuracion).interruptores = cantidad;
	} else if(strcmp(NOMBRE_PORTALES, nombre_elemento) == 0) {
		(*configuracion).portales = cantidad;
	} else if(strcmp(NOMBRE_MONEDAS, nombre_elemento) == 0) {
		(*configuracion).monedas = cantidad;
	} else if(strcmp(NOMBRE_ESCALERAS, nombre_elemento) == 0) {
		(*configuracion).escaleras = cantidad;
	} else if(strcmp(NOMBRE_LLAVES, nombre_elemento) == 0) {
		(*configuracion).llaves = cantidad;
	}
}

/*
	Pre: Recibimos configuraciones que no esten vacias, sino con valores por defecto.
	Tambien necesitamos que exista un archivo llamado "config.txt" para ser leido, y 
	con un formato concreto
	Post: Leemos las configuraciones que hay en el archivo y las aplicamos sobre las
	configuraciones pasadas por parametro
*/
int config_juego(config_t configuraciones[MAX_CONFIG]) {
	FILE* arch = fopen(ARCHIVO_CONFIG, "r");
	if(!arch) {
		perror("Error to open file: config.txt");
		return ERROR;
	}

	int leidos;
	int numero_nivel;
	char nombre_elemento[MAX_ELEMENTO];
	int cantidad;

	leidos = fscanf(arch, FORMATO_LECTURA_CONFIG, &(numero_nivel), nombre_elemento, &(cantidad));
	while(leidos == LEIDOS_CONFIG) {
		establecer_cantidad_elemento(&(configuraciones[numero_nivel - 1]), cantidad, nombre_elemento);
		leidos = fscanf(arch, FORMATO_LECTURA_CONFIG, &(numero_nivel), nombre_elemento, &(cantidad));
	}

	fclose(arch);
	return EXITO;
}