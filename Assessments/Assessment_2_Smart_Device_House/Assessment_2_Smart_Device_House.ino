//Import Libs
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include "RTClib.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);



Servo servo; //Delcare servo



// Real Time Clock (RTC)
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.

//Pins
#define ServoPin  24
#define mDrive1  7
#define mDrive2  6
#define potPin  A8
#define sdSelect  41
#define redLED  31
#define YellLED  30
#define greenLED 32
#define line  49
#define button  3
#define echo  4
#define Trig  5
#define buzzer  40

//Defines
#define TrigDistance 100


void setup() {
  //Setup pins
  pinMode(mDrive1, OUTPUT);
  pinMode(mDrive2, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(YellLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(line, INPUT);
  pinMode(button, INPUT);
  pinMode(potPin, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(echo, INPUT);
  servo.attach(ServoPin);       //Set up servo
  Serial.begin(9600);           // Open serial communications and wait for port to open:
  while (!Serial) {
    delay(1);                   // wait for serial port to connect. Needed for native USB port only
  }
  ss.begin(GPSBaud);
  Serial.print("Initializing SD card...");
  if (!SD.begin(sdSelect)) {
    Serial.println("initialization failed!");
    while (1);
  }
// Real Time Clock (RTC)
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("initialization done.");
logEvent("System Initialisation...");
}

void loop() {

}




void logEvent(String dataToLog) {
  /*
     Log entries to a file on an SD card.
  */
  // Get the updated/current time
  DateTime rightNow = rtc.now();

  // Open the log file
  File logFile = SD.open("events.csv", FILE_WRITE);
  if (!logFile) {
    Serial.print("Couldn't create log file");
    abort();
  }

  // Log the event with the date, time and data
  logFile.print(rightNow.year(), DEC);
  logFile.print(",");
  logFile.print(rightNow.month(), DEC);
  logFile.print(",");
  logFile.print(rightNow.day(), DEC);
  logFile.print(",");
  logFile.print(rightNow.hour(), DEC);
  logFile.print(",");
  logFile.print(rightNow.minute(), DEC);
  logFile.print(",");
  logFile.print(rightNow.second(), DEC);
  logFile.print(",");
  logFile.print(dataToLog);

  // End the line with a return character.
  logFile.println();
  logFile.close();
  Serial.print("Event Logged: ");
  Serial.print(rightNow.year(), DEC);
  Serial.print(",");
  Serial.print(rightNow.month(), DEC);
  Serial.print(",");
  Serial.print(rightNow.day(), DEC);
  Serial.print(",");
  Serial.print(rightNow.hour(), DEC);
  Serial.print(",");
  Serial.print(rightNow.minute(), DEC);
  Serial.print(",");
  Serial.print(rightNow.second(), DEC);
  Serial.print(",");
  Serial.println(dataToLog);
}

boolean Read_distance() {
  long duration; 
  int distance;
  // Clears the trigPin condition
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  if (distance <= TrigDistance) {
    return(true);
  }
  else {
    return(false);
  }
}
