int PotPins[] = {A0,A1,A2,A3,A4};
int PinsSize = sizeof(PotPins) / sizeof(int);
int PotReadout[] = {};

void setup() {
 Serial.begin(9600);
 for (int i = 0; i <= PinsSize; i++)   {
    pinMode(PotPins[i], INPUT);
  }
}

void loop() {
  readPins();
    avrage();
  
}


void readPins() {
    for (int i = 0; i < PinsSize; i++)   {
    PotReadout[i] = analogRead(PotPins[i]);
    delay(500);
  }
}

int avrage() {
  int avragePot = 0;
  for (int i = 0; i < PinsSize; i++)   {
  avragePot = avragePot + PotReadout[i];
    Serial.print(PotReadout[i]);
    Serial.print(",");
  }  
  avragePot = avragePot/PinsSize;
  
  
}
