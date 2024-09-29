#include "globals.h"  // Incluimos las variables y constantes globales
#include "ledControl.h"  // Incluimos el control de LEDs
#include "listenImpact.h" 
#include "listenButton.h"
#include "listenKy002.h"

unsigned long lastImpactTime = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("Setting up");

    // Usamos PULLUP interno para evitar lecturas erráticas
    pinMode(BUTTON_PIN, INPUT_PULLUP); 
    // Inicializamos el sensor ky-002 (sensor de impactos) 
    pinMode(KY002_SENSOR_PIN, INPUT);
    // Inicialización de la tira LED
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.clear();  // Apagar todos los LEDs al inicio
    FastLED.show();
    int sensorValue = analogRead(SOUND_SENSOR_PIN);
    fillAmbianceWith(sensorValue);
    Serial.println("Set up done.");

}

void doBlinking(){
    if(millis() > nextBlink){
        unsigned long remaining = (lastImpactTime + RESET_TIME) - millis();
        toggleLeds();
        nextBlink = millis() + (remaining/6);
    }
}

void loop() {
    int detectedEvents = 0;
    detectedEvents += listenImpact();
    detectedEvents += listenButton();
    detectedEvents += listenKy002();

    if(detectedEvents>0){
        impactCounter+=detectedEvents;
        Serial.print("New impact, counter:");
        Serial.println(impactCounter);
        updateLedColor(impactCounter);
        nextBlink=millis()+BLINK_TIME;
        lastImpactTime=millis();
        digitalWrite(5, HIGH);
    }
  
    // Do blinking progresively
    if(impactCounter > 0 && nextBlink < millis()){
        doBlinking();
    }
    
    // Turn off.
    if(impactCounter > 0 && lastImpactTime+RESET_TIME < millis()){  
        Serial.println("Completely turn off....");
        FastLED.clear();
        FastLED.show();
        digitalWrite(5, LOW);
        impactCounter=0;
    }
    
}
