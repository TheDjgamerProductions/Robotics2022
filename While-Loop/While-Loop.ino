int x = 2;
void setup()
{
  do {
   pinMode(x, OUTPUT);;
   x++;
  } while (x != 5);
  x = 2;
  
}

void loop() {
	
  while (x != 6) {
    digitalWrite(x, HIGH);
  	x++;
    delay(100);
} 
  delay(1000);
  while (x != 1) {
    digitalWrite(x, LOW);
  	x--;
    delay(100);
} 
  delay(1000);
  
}
