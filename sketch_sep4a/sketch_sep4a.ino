int ledRed = 4;
int ledYellow = 5;
int ledGreen = 6;
int sound_sensor = A0; //assign to pin A2
int sensorValue;
int minimumSound = 50;
int ledLevel = 0;
unsigned long time;

int lastElms[256] = {0};
int count=0;
int ambianceSoundLevel = 0;

int calcAmbianceSoundLevel(){
    unsigned long int curSum = 0;
    for(int i = 0; i < 256; i++){
        curSum = curSum + lastElms[i];
    }
    ambianceSoundLevel = curSum/256;
    return ambianceSoundLevel;
}

void addCurrent(int value){
  lastElms[count]=value;
  count+=1;
  if(count==256){
    calcAmbianceSoundLevel();
    count=0;
  }
}

void handleLeds(){
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, LOW);
  switch(ledLevel){
    case 3:
      digitalWrite(ledGreen, HIGH);
    case 2:
      digitalWrite(ledYellow, HIGH);
    case 1:
      digitalWrite(ledRed, HIGH);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Seting up.");
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
}

void loop() {
  // get the analog value
  sensorValue = analogRead(sound_sensor);
   if(sensorValue>minimumSound){
      addCurrent(sensorValue);
      if(sensorValue>(ambianceSoundLevel*1.7) && ambianceSoundLevel>0){  
          Serial.println(" ****************************** ");
          Serial.print("ambianceSoundLevel: ");
          Serial.print(ambianceSoundLevel);
          Serial.print(" :: sensorValue: ");
          Serial.println(sensorValue);
        //Serial.println(sensorValue);
          ledLevel+=(ledLevel==3?0:1);
          handleLeds();
          time = millis();
      }
      
      if(ledLevel > 0 && time+1000<millis()){
        ledLevel-=1;
        time = millis();
        handleLeds();
      }
      
   }
}
