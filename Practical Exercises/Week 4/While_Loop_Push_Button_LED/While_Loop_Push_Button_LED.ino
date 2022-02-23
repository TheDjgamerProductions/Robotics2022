void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  
}

void loop()
{
  while (digitalRead(2) == HIGH) {
    digitalWrite(13, HIGH);
  }
    digitalWrite(13, LOW);
  delay(25);
}
