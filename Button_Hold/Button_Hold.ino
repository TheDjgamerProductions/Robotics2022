void setup()
{
  pinMode(10, OUTPUT);
  pinMode(2, INPUT);
}

void loop()
{
  while (digitalRead(2) == HIGH) {
    digitalWrite(10, HIGH);
  }
  digitalWrite(10, LOW);
}
