void setup()
{
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
  while (1 == 1) {
  	digitalWrite(5, HIGH);
    digitalWrite(2, HIGH);
  	delay(1000); 
  	digitalWrite(2, LOW);
    digitalWrite(5, LOW);
  	delay(1000); 
  }
}

void loop()
{
  

}
