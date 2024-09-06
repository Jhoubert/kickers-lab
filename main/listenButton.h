#include "globals.h"  // Incluimos las variables y constantes globales

int listenButton() {
  if (digitalRead(BUTTON_PIN) == LOW) {  // Lógica inversa por el INPUT_PULLUP
    Serial.print("Boton detectado. Contador: ");
    return 1;
  }
  return 0;
}
