#include "globals.h"  // Incluimos las variables y constantes globales

void calculateAmbianceLevel() {
  unsigned long int curSum = 0;

  for (int i = 0; i < SOUND_LOG_SIZE; i++) {
    curSum = curSum + sound_log[i];
  }
  ambianceSoundLevel = curSum / SOUND_LOG_SIZE;
}

void fillAmbianceWith(int val){
  for (int i = 0; i < SOUND_LOG_SIZE; i++) {
    sound_log[i] = val;
  }
  ambianceSoundLevel = val;
  Serial.println("Initial ambiance created.");
}

void logCurrentLevel(int value) {
  sound_log[log_pos] = value;
  log_pos += 1;
  if (log_pos == SOUND_LOG_SIZE) {
    calculateAmbianceLevel();
    log_pos = 0;
  }
}

int listenImpact() {  
  int sensorValue = analogRead(SOUND_SENSOR_PIN);
  if (sensorValue > MIN_SOUND_LEVEL) {
    logCurrentLevel(sensorValue);
    if (ambianceSoundLevel > 0 && sensorValue > ambianceSoundLevel*1.6){
      Serial.print("Impact received -> ambianceSoundLevel: ");
      Serial.print(ambianceSoundLevel);
      Serial.print(" :: sensorValue: ");
      Serial.println(sensorValue);
      return 1;
    }
  }
  return 0;
}
