int greenLED = 10;
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(greenLED, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(greenLED, HIGH);
  delay(1000); 
}
