#ifndef __CONSTANTES__
#define __CONSTANTES__

/*
	Biblioteca donde se almacenan las constantes que se van a usar a lo largo
	de todo el juego
*/

// Estados de juego

#define ESTADO_JUGANDO  0
#define ESTADO_GANADO   1
#define ESTADO_PERDIDO -1

// Puntos

#define MIN_MONEDAS 10
#define MAX_MONEDAS 10

#define APAGAR_VELA 50

#define MIN_PUNTOS_VIDA 200
#define MAX_VIDAS         3

// Movimientos

#define ARRIBA    'W'
#define DERECHA   'D'
#define ABAJO     'S'
#define IZQUIERDA 'A'
#define VIDA      'V'

// Emojis para el juego

#define EMOJI_MAC  "👦"
#define EMOJI_BLOO "👻"

#define EMOJI_PARED "🧱"
#define EMOJI_SUELO "🟩"

#define EMOJI_PUERTA      "🚪"
#define EMOJI_ESCALERA    "🪜"
#define EMOJI_LLAVE       "🔑"
#define EMOJI_MONEDA      "🪙"
#define EMOJI_POZOS 	  "⬛"
#define EMOJI_INTERRUPTOR "🔁"
#define EMOJI_PORTAL 	  "☎️"
#define EMOJI_VELA        "🕯️"

// Conveciones de personajes, obstaculos y herraminetas

#define MAC  'M'
#define BLOO 'B'

#define PUERTA        'D'
#define ESCALERAS     'E'
#define LLAVE         'L'
#define MONEDAS       'C'
#define POZOS         'W'
#define INTERRUPTORES 'O'
#define PORTALES      'P'
#define VELAS         'V'

#define PARED '*'
#define SUELO '_'

// Cantidades para los tres niveles

#define CANT_PUERTAS 1

// - Nivel 1

#define NIVEL_UNO  1

#define CANT_VELAS_UNO          5
#define CANT_POZOS_UNO         15
#define CANT_INTERRUPTORES_UNO  1
#define CANT_PORTALES_UNO       0
#define CANT_ESCALERAS_UNO     10
#define CANT_MONEDAS_UNO       10
#define CANT_LLAVES_UNO         0

// - Nivel 2

#define NIVEL_DOS  2

#define CANT_VELAS_DOS         10
#define CANT_POZOS_DOS         20
#define CANT_INTERRUPTORES_DOS  2
#define CANT_PORTALES_DOS       2
#define CANT_ESCALERAS_DOS     15
#define CANT_MONEDAS_DOS       15
#define CANT_LLAVES_DOS         1

// - Nivel 3

#define NIVEL_TRES 3

#define CANT_VELAS_TRES         12
#define CANT_POZOS_TRES         30
#define CANT_INTERRUPTORES_TRES  4
#define CANT_PORTALES_TRES       4
#define CANT_ESCALERAS_TRES     15
#define CANT_MONEDAS_TRES       15
#define CANT_LLAVES_TRES         1

// Condiciones iniciales del personaje y su sombra

#define VIDAS_INICIALES          3
#define PUNTOS_INICIALES         0
#define TIENE_LLAVE          false
#define INTERRUPTOR_APRETADO false 

#define ESTA_VIVA true

// Modos para arrancar el juego

#define JUGAR 'J'
#define TEST  'T'
#define SALIR 'Q'

#endif