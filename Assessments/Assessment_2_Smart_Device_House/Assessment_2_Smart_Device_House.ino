//Import Libs
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include "RTClib.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <L298N.h>






Servo servo; //Delcare servo



// Real Time Clock (RTC)
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.

//Pins
#define ServoPin  24
#define mDrive1  7
#define mDrive2  6
#define sdSelect  41
#define redLED  8
#define YellLED  9
#define greenLED 32
#define line  49
#define button  3
#define echo  12
#define Trig  13
#define buzzer  40


//Defines
#define TrigDistance 10

//Vars
const char *gpsStream =
  "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
  "$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n"
  "$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77\r\n"
  "$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C\r\n"
  "$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D\r\n"
  "$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\r\n"; \
static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 9600;
boolean fanState = false;
int x = 1;
int PrevEventID = 1;
String PrevEvent1;
String PrevEvent2;


// The TinyGPS++ object
TinyGPSPlus gps;
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
L298N motor(mDrive1, mDrive2);


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
  pinMode(A0, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(echo, INPUT);
  servo.attach(ServoPin);       //Set up servo
  Serial.begin(115200);           // Open serial communications and wait for port to open:
  ss.begin(GPSBaud);
  while (!Serial) {
    delay(1);                   // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(sdSelect)) {
    Serial.println("initialization failed!");
    while (1);
  }
  while (*gpsStream)
    if (gps.encode(*gpsStream++))
      getGPSInfo();
  // Real Time Clock (RTC)
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("initialization done.");
  logEvent("System Initialisation...");
}

void loop() {
  stateHandeler();
  //getGPSInfo();
  delay(50);
}



/*

   @pram string (What data to log)
   @return null
*/

void logEvent(String dataToLog) {
  /*
     Log entries to a file on an SD card.
  */
  // Get the updated/current time
  if (PrevEvent1 == dataToLog || PrevEvent2 == dataToLog) {
    Serial.println("Dupe Data");
  }
  else {
    DateTime rightNow = rtc.now();

    // Open the log file
    File logFile = SD.open("events.csv", FILE_WRITE);
    if (!logFile) {
      Serial.print("Couldn't create log file");
      abort;
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
    if (PrevEventID == 1) {
      PrevEvent1 = dataToLog;
      PrevEventID = 2;
    }
    else {
      PrevEvent2 = dataToLog;
      PrevEventID = 1;
    }
   logFile.flush();
   logFile.close();
  }
}

/*

   @pram null
   @return boolean
*/
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
  Serial.println(distance);
  if (distance <= TrigDistance) {
    return (true);
  }
  else {
    return (false);
  }
}

/*
   This function is used to make the house in an armed state if the GPS is outside the house
   @pram null
   @return null
*/
void stateHandeler() {
  if (1 != 1) { //This code is used to see if the GPS is inside the house for now it is returning true all the time, this will change afer i get the GPS to work
    disarmedState();
  }
  else {
    armedState();
  }


}

/*

   @pram null
   @return null
*/
void disarmedState() {
  LockController(false);
  ledController();
  fanController();
}

/*

   @pram null
   @return null
*/
void armedState() {
  LockController(true);
  if (Read_distance()) {
    tone(buzzer, 800);
    digitalWrite(redLED, HIGH);
    delay(25);
    tone(buzzer, 700);
    digitalWrite(redLED, LOW);
    delay(25);
    logEvent("Alarm Went off");
  }
  else {
    noTone(buzzer);
    digitalWrite(redLED, LOW);
    logEvent("Alarm deactivated");
  }

}

/*

   @pram null
   @return null
*/
void ledController() {
  int potRead = analogRead(A0);
  int ledLevel = map(potRead, 0, 1023, 0, 255);
  Serial.println(ledLevel);
  int lineReadout = digitalRead(line);
  if (!lineReadout) {
    analogWrite(YellLED, ledLevel);
  }
  else {
    digitalWrite(YellLED, LOW);
  }

}

/*

   @pram null
   @return null
*/
void fanController() {
  if (fanState) {
    while (digitalRead(button) == 0) {
      Serial.println("Button");
      fanState = false;
      logEvent("Fan Off");

    }
    motor.forward();
  }
  else {
    while (digitalRead(button) == 0) {
      fanState = true;
      logEvent("Fan on");
    }
    motor.stop();
  }
}

void getGPSInfo() {
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

void LockController(boolean lock) {
  if (lock) {
    servo.write(90);
    logEvent("Locked");
  }
  else {
    servo.write(0);
    logEvent(String(x));
    x += 1;
  }
}
