void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  
}

void loop()
{
  if (digitalRead(2) == HIGH) {
	digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
  }
  delay(25);
}
