bool Toggle = false;
int i = 0;
  
  
  
  
void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  if (digitalRead(2) == HIGH) {
    Toggle = !Toggle;
    Serial.println(Toggle);
    while (digitalRead(2) == HIGH) { //Supporting code to prevent weird behaviour with bounce and when the user holds down the button
    }
  }
  switch (Toggle) {
    
    case false:
    	digitalWrite(13, LOW);
    	break;
    case true:    
    	digitalWrite(13, HIGH);
    	break;
  }
  delay(25);
}
