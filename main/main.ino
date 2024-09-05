#include "globals.h"  // Incluimos las variables y constantes globales
#include "ledControl.h"  // Incluimos el control de LEDs

unsigned long lastImpactTime = 0;

void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT_PULLUP);  // Usamos PULLUP interno para evitar lecturas erráticas
    
    // Inicialización de la tira LED
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.clear();  // Apagar todos los LEDs al inicio
    FastLED.show();
    
    Serial.println("Sistema inicializado.");
}

void loop() {
    // Verificar si se presiona el botón para registrar un impacto
    if (digitalRead(BUTTON_PIN) == LOW) {  // Lógica inversa por el INPUT_PULLUP
        impactCounter++;  // Actualiza el contador global
        lastImpactTime = millis();
        Serial.print("Impacto detectado. Contador: ");
        Serial.println(impactCounter);
        updateLedColor();  // Actualiza el color de la tira LED según los impactos
        delay(200);  // Debounce simple
    }

    // Si ha pasado suficiente tiempo sin impactos
    if (millis() - lastImpactTime > RESET_TIME && impactCounter > 0) {
        // Iniciar el parpadeo con aceleración
        unsigned long blinkStartTime = millis();
        unsigned long blinkElapsedTime = 0;

        // Parpadeo acelerado durante BLINK_DURATION
        while (blinkElapsedTime < BLINK_DURATION) {
            blinkElapsedTime = millis() - blinkStartTime;

            // Verificar si se ha recibido un nuevo impacto durante el parpadeo
            if (digitalRead(BUTTON_PIN) == LOW) {
                // Si se detecta un impacto, detener el parpadeo y continuar con la secuencia de colores
                impactCounter++;
                lastImpactTime = millis();
                Serial.print("Impacto detectado durante el parpadeo. Contador: ");
                Serial.println(impactCounter);
                updateLedColor();
                return;  // Salir del parpadeo y continuar en el loop
            }

            // Calculamos la velocidad del parpadeo, que se acelera con el tiempo
            int blinkDelay = map(blinkElapsedTime, 0, BLINK_DURATION, 200, 50);  // Parpadeo más rápido

            // Encender la tira LED
            updateLedColor();
            delay(blinkDelay);

            // Apagar la tira LED (parpadeo)
            FastLED.clear();
            FastLED.show();
            delay(blinkDelay);
        }

        // Si no hubo impactos durante el parpadeo, reiniciar el contador
        impactCounter = 0;
        FastLED.clear();  // Apagar todos los LEDs al reiniciar
        FastLED.show();
    }
}
