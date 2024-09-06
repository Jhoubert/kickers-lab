#include "globals.h"  // Incluimos las variables y constantes globales

int count = 0;
int ambianceSoundLevel = 0;

int calculateAmbianceLevel() {
  unsigned long int curSum = 0;
  for (int i = 0; i < SOUND_LOG_SIZE; i++) {
    curSum = curSum + sound_log[i];
  }
  ambianceSoundLevel = curSum / SOUND_LOG_SIZE;
  return ambianceSoundLevel;
}

void logCurrentLevel(int value) {
  sound_log[count] = value;
  count += 1;
  if (count == SOUND_LOG_SIZE) {
    calculateAmbianceLevel();
    count = 0;
  }
}

int listenImpact() {
  int sensorValue = analogRead(SOUND_SENSOR_PIN);
  if (sensorValue > MIN_SOUND_LEVEL) {
    logCurrentLevel(sensorValue);
    if (sensorValue > (ambianceSoundLevel * 1.6) && ambianceSoundLevel > 0) {
      Serial.print("Impact received -> ambianceSoundLevel: ");
      Serial.print(ambianceSoundLevel);
      Serial.print(" :: sensorValue: ");
      Serial.println(sensorValue);
      return 1;
    }
  }
  return 0;
}
