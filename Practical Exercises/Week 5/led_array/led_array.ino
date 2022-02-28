int Pins[] = {2,3,4,5,6,7,8,9,10,11,12};
int PinsSize = sizeof(Pins) / sizeof(int);
int i = 0;
void setup()
{
  Serial.begin(9600);
  for (int i = 0; i <= PinsSize; i++)   {
    Serial.println(Pins[i]);
    pinMode(Pins[i], OUTPUT);
  }

}

void loop()
{
  for (int i = 0; i <= PinsSize; i++)   {
    analogWrite(Pins[i], random(255));
  	delay(100);
  }
  i = 0;
}
