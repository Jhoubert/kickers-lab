#include "globals.h"  // Incluimos las variables y constantes globales

int listenKy002() {
  if (digitalRead(KY002_SENSOR_PIN) == LOW) {  // Lógica inversa por el INPUT_PULLUP
    Serial.println("Sensor ky002 detectado.");
    return 1;
  }
  return 0;
}
