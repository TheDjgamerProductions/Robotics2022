int echo_pin = 6;
int trigger_pin = 3;
int PIR_pin = 5;
int button_pin = 4;
int led_pin = 2;
bool active = false;
long duration; 
int distance;
boolean readout[3];


void setup() {
  pinMode(echo_pin, INPUT);
  pinMode(trigger_pin, OUTPUT);
  pinMode(PIR_pin, INPUT);
  pinMode(button_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
  }
          
void loop() {
	read_sensors();
  	digitalWrite(led_pin, trigger_checker());
  }

  
boolean Read_distance() {
  // Clears the trigPin condition
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo_pin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  if (distance <= 100) {
    return(true);
  }
  else {
    return(false);
  }
}

boolean Read_PIR() {
  return(digitalRead(PIR_pin));
}


boolean Read_Button() {
  return(digitalRead(button_pin));
}

void read_sensors() {
  readout[0] = Read_distance();
  readout[1] = Read_PIR();
  readout[2] = Read_Button();
}

boolean trigger_checker() {
  int s = 0;
  for (int i = 0; i < 3; i++){
    s += readout[i];
	Serial.println(s);
  }
  if (s >= 2) {
    return(true);
  }
  else {
    return(false);
  }
  
}

