#ifndef GLOBALS_H
#define GLOBALS_H

#include <FastLED.h>  // Incluir la librería FastLED
// Tiempo antes de reiniciar el contador, durante el cual habrá un parpadeo acelerado
const unsigned long RESET_TIME = 5000;      // 5 segundos sin impacto para reiniciar el contador
const unsigned long BLINK_TIME = 3000;  // 3 segundos para comenzar a parpadear


// Definición del número de LEDs y el pin de datos
#define NUM_LEDS 30  // Número de LEDs en la tira
#define DATA_PIN 8    // Pin donde conectaremos el pin de datos de la tira RGB
#define BUTTON_PIN 7

#define SOUND_SENSOR_PIN A0
#define MIN_SOUND_LEVEL 50
#define SOUND_LOG_SIZE 256

// Variables y constantes globales
extern int impactCounter;  // Contador de impactos

// Definición de colores para la tira LED
const CRGB RGB_COLORS[] = { CRGB(255, 0, 0), CRGB(255, 255, 0), CRGB(0, 255, 0), CRGB(0, 0, 255) };  // Colores para la tira LED
const int IMPACTS_TO_NEXT_COLOR = 6;                                                                 // Impactos necesarios para cambiar de color

// Definición del array de LEDs
extern CRGB leds[NUM_LEDS];  // Arreglo para los LEDs de la tira


extern int sound_log[SOUND_LOG_SIZE];
extern int log_pos;
extern bool isLedOn;
extern unsigned long nextBlink;
extern int ambianceSoundLevel;


#endif
