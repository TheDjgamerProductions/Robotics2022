const int potPin = A0;

const int ledPin = 13;

const int threshold = 400;

void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop()
{
  if (analogRead(A0) >= threshold) {
    digitalWrite(ledPin,HIGH);	
  }
  else {
    digitalWrite(ledPin,LOW);
    
  }
}
