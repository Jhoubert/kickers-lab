#include "globals.h"

// Definición e inicialización de las variables globales
int impactCounter = 0;  // Iniciamos el contador de impactos
bool isLedOn = false;
int ambianceSoundLevel = 0;
extern unsigned long nextBlink = 0;

int sound_log[SOUND_LOG_SIZE] = {0};
int log_pos = 0;

// Definición del array de LEDs
CRGB leds[NUM_LEDS];  // Array que contiene los LEDs de la tira
