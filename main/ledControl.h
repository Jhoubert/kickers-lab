#include "globals.h"  // Incluimos las variables y constantes globales

#ifndef LEDCONTROL_H
#define LEDCONTROL_H

// Función para interpolar entre dos colores
CRGB interpolateColor(CRGB color1, CRGB color2, float ratio) {
  // Interpolar cada componente del color
  uint8_t red = (uint8_t)((1.0 - ratio) * color1.r + ratio * color2.r);
  uint8_t green = (uint8_t)((1.0 - ratio) * color1.g + ratio * color2.g);
  uint8_t blue = (uint8_t)((1.0 - ratio) * color1.b + ratio * color2.b);

  // Imprimir los valores de interpolación para depuración
  Serial.print("Interpolando entre colores: R1=");
  Serial.print(color1.r);
  Serial.print(", G1=");
  Serial.print(color1.g);
  Serial.print(", B1=");
  Serial.print(color1.b);
  Serial.print(" y R2=");
  Serial.print(color2.r);
  Serial.print(", G2=");
  Serial.print(color2.g);
  Serial.print(", B2=");
  Serial.print(color2.b);
  Serial.print(" con ratio: ");
  Serial.println(ratio);

  Serial.print("Color resultante: R=");
  Serial.print(red);
  Serial.print(", G=");
  Serial.print(green);
  Serial.print(", B=");
  Serial.println(blue);

  return CRGB(red, green, blue);
}

// Función para actualizar el color de la tira LED según el número de impactos
void updateLedColor(int counter) {
  if (counter == 0) {
    // Si no hay impactos, apagar la tira LED
    FastLED.clear();
  } else {
    // Calcular el índice actual de color y el siguiente
    int currentColorIndex = (counter - 1) / IMPACTS_TO_NEXT_COLOR;
    int nextColorIndex = currentColorIndex + 1;

    // Limitar el índice dentro del rango de colores disponibles
    if (currentColorIndex >= sizeof(RGB_COLORS) / sizeof(RGB_COLORS[0])) {
      currentColorIndex = sizeof(RGB_COLORS) / sizeof(RGB_COLORS[0]) - 1;
    }

    if (nextColorIndex >= sizeof(RGB_COLORS) / sizeof(RGB_COLORS[0])) {
      nextColorIndex = sizeof(RGB_COLORS) / sizeof(RGB_COLORS[0]) - 1;
    }

    // Calcular cuántos impactos han ocurrido dentro del rango actual
    int impactsInCurrentRange = (counter - 1) % IMPACTS_TO_NEXT_COLOR;
    float ratio = (float)impactsInCurrentRange / (IMPACTS_TO_NEXT_COLOR - 1);  // Ajuste en el ratio

    // Interpolar entre el color actual y el siguiente
    CRGB interpolatedColor = interpolateColor(RGB_COLORS[currentColorIndex], RGB_COLORS[nextColorIndex], ratio);

    // Actualizar todos los LEDs con el color interpolado
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = interpolatedColor;
    }
  }

  // Mostrar los cambios en la tira LED
  FastLED.show();
}

void toggleLeds(){

        Serial.print(millis());
    if(isLedOn){
        Serial.println(" -> Turning leds off");
        FastLED.clear();
        FastLED.show();
        isLedOn=false;
    }else{
        Serial.println(" -> Turning leds on");
        updateLedColor(impactCounter);
        isLedOn=true;
    }
}


#endif
