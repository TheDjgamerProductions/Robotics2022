int PotPins[] = {A0,A1,A2,A3,A4};
int LEDPins[] = {2,3,4,5,6};
int PotPinsSize = sizeof(PotPins) / sizeof(int);
int LEDPinsSize = sizeof(LEDPins) / sizeof(int);
int PotReadout[5];

void setup() {
 Serial.begin(9600);
 for (int i = 0; i < PotPinsSize; i++)   {
    pinMode(PotPins[i], INPUT);
  }
 for (int i = 0; i < LEDPinsSize; i++)   {
    pinMode(LEDPins[i], OUTPUT);
  }
}

void loop() {
  
  readPins();
  avrage();
  updateLED();
}


void readPins() {
    for (int i = 0; i < PotPinsSize; i++)   {
      PotReadout[i] = analogRead(PotPins[i]);
      delay(50);
  }
}

int avrage() {
  int avragePot = 0;
  for (int i = 0; i < PotPinsSize; i++)   {
  avragePot = avragePot + PotReadout[i];
    Serial.print(PotReadout[i]);
    Serial.print(",");
  }  
  avragePot = avragePot/PotPinsSize;
  Serial.print("The avrage is: ");
  Serial.println(avragePot);
  
}

void updateLED() {
  for (int i = 0; i < PotPinsSize; i++) {
    int x = map(PotReadout[i], 0, 1023, 0, 255);
    analogWrite(LEDPins[i], x);
    
    
  }
  
 
  
  
}
