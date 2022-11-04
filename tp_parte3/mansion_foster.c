#include "mansion_foster.h"

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
void arrancar_juego(config_t configuraciones[MAX_CONFIG]) {
	char modo = ' ';
	int estado_juego = -1;

	do {
		pedir_modo_inicio(&modo);
		if(modo == JUGAR) {	
			do {
				juego_t juego;
				inicializar_juego(&juego, configuraciones);
				estado_juego = arrancar_partida(&juego);
			} while(estado_juego != ESTADO_PERDIDO && estado_juego != ESTADO_GANADO);
		} else if(modo == TEST) {
			probar_funcionalidades();
		}
	} while(modo != SALIR);
}


/*
	Pre: Recibimos las configuraciones ya inicializadas
	Post: Imprimimos la presentacion y arrancamos el juego
*/
void arrancar_programa(config_t configuraciones[MAX_CONFIG]) {
	srand ((unsigned)time(NULL));
	system("clear");

	imprimir_presentacion();
	arrancar_juego(configuraciones);
}

/*
	Pre: Recibimos las configuraciones vacias
	Post: Agregamos a configuraciones, los valores por defecto
*/
void inicializar_config(config_t configuraciones[MAX_CONFIG]) {
	int numero_nivel = NIVEL_UNO;

	configuraciones[numero_nivel - 1].numero_nivel = numero_nivel;
	configuraciones[numero_nivel - 1].pozos = CANT_POZOS_UNO;
	configuraciones[numero_nivel - 1].velas = CANT_VELAS_UNO;
	configuraciones[numero_nivel - 1].interruptores = CANT_INTERRUPTORES_UNO;
	configuraciones[numero_nivel - 1].portales = CANT_PORTALES_UNO;
	configuraciones[numero_nivel - 1].monedas = CANT_MONEDAS_UNO;
	configuraciones[numero_nivel - 1].escaleras = CANT_ESCALERAS_UNO;
	configuraciones[numero_nivel - 1].llaves = CANT_LLAVES_UNO;

	numero_nivel++;

	configuraciones[numero_nivel - 1].numero_nivel = numero_nivel;
	configuraciones[numero_nivel - 1].pozos = CANT_POZOS_DOS;
	configuraciones[numero_nivel - 1].velas = CANT_VELAS_DOS;
	configuraciones[numero_nivel - 1].interruptores = CANT_INTERRUPTORES_DOS;
	configuraciones[numero_nivel - 1].portales = CANT_PORTALES_DOS;
	configuraciones[numero_nivel - 1].monedas = CANT_MONEDAS_DOS;
	configuraciones[numero_nivel - 1].escaleras = CANT_ESCALERAS_DOS;
	configuraciones[numero_nivel - 1].llaves = CANT_LLAVES_DOS;

	numero_nivel++;

	configuraciones[numero_nivel - 1].numero_nivel = numero_nivel;
	configuraciones[numero_nivel - 1].pozos = CANT_POZOS_TRES;
	configuraciones[numero_nivel - 1].velas = CANT_VELAS_TRES;
	configuraciones[numero_nivel - 1].interruptores = CANT_INTERRUPTORES_TRES;
	configuraciones[numero_nivel - 1].portales = CANT_PORTALES_TRES;
	configuraciones[numero_nivel - 1].monedas = CANT_MONEDAS_TRES;
	configuraciones[numero_nivel - 1].escaleras = CANT_ESCALERAS_TRES;
	configuraciones[numero_nivel - 1].llaves = CANT_LLAVES_TRES;
}

/*
	Pre: Recibimos un char que corresponde o no a un programa a ejecutar
	Post: Ejecutamos el programa en caso de existir, de lo contrario imprimimos
	un mensaje por pantalla
*/
void manejar_programa(int argc, char* argv[], config_t configuraciones[MAX_CONFIG]) {
	if(strcmp(argv[1], AGREGAR_PARTIDA) == 0 && argc == 3) {
		agregar_partida(argv[2]);
	} else if(strcmp(argv[1], ELIMINAR_PARTIDA) == 0 && argc == 4) {
		eliminar_partida(argv[2], argv[3]);
	} else if(strcmp(argv[1], ORDENAR_PARTIDA) == 0 && argc == 3) {
		ordenar_partidas(argv[2]);
	} else if(strcmp(argv[1], CONFIG_JUEGO) == 0 && argc == 2) {
		config_juego(configuraciones);
		arrancar_programa(configuraciones);
	} else {
		printf("Error: el programa no existe\n");
	}
}

int main(int argc, char* argv[]) {
	config_t configuraciones[MAX_CONFIG];
	inicializar_config(configuraciones);

	if(argc == 1) {
		arrancar_programa(configuraciones);	
	} else {
		manejar_programa(argc, argv, configuraciones);
	}
	
	return 0;
}
