
int output = 0;



void setup()
{
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  potReadAndAvrage();
    Serial.println(output);
  upateLED(output);


}

int potReadAndAvrage() {
  output = map((analogRead(A0) + analogRead(A1))/2, 0, 1023, 0, 255);
  return output;
}


void upateLED(int x) {
 analogWrite(6, x);
}
