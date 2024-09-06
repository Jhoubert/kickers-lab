#include "globals.h"  // Incluimos las variables y constantes globales
#include "ledControl.h"  // Incluimos el control de LEDs
#include "listenImpact.h" 
#include "listenButton.h"

unsigned long lastImpactTime = 0;

void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT_PULLUP);  // Usamos PULLUP interno para evitar lecturas erráticas
    
    // Inicialización de la tira LED
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.clear();  // Apagar todos los LEDs al inicio
    FastLED.show();
    Serial.println("Set up done.");
}

void doBlinking(){
    int nextBlinkTime = lastImpactTime+BLINK_DURATION+nextBlink;
    if(millis > nextBlinkTime){
        toggleLeds();
        if(nextBlink==0){
          nextBlink = BLINK_DURATION;
        }
        nextBlink = millis()-(nextBlinkTime/8);

        Serial.print(" -> Next blink on:");
        Serial.println(nextBlink);
    }
}

void loop() {
    int impact = listenImpact();
    int press = listenButton();
    
    impactCounter+=impact+press;
    if(impact == 1 || press == 1){
        updateLedColor(impactCounter);
    }

    // Do blinking progresively
    if(impactCounter > 0 && lastImpactTime+BLINK_DURATION > millis()){
        doBlinking();
    }
    
    // Turn off.
    if(impactCounter > 0 && lastImpactTime+RESET_TIME > millis()){  
        FastLED.clear();
        FastLED.show();
        impactCounter=0;
    }
    
}
