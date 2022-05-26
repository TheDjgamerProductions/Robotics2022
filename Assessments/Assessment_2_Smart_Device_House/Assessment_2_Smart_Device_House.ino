//https://forum.arduino.cc/t/multiple-spi-devices-on-mega/629412/4


// SD Card Module
#include <SPI.h>
#include <SD.h>
#include "Adafruit_BLE_UART.h"



// Real Time Clock (RTC)
#include "RTClib.h"
RTC_Millis rtc;     // Software Real Time Clock (RTC)
DateTime rightNow;  // used to store the current time.

#define ServoPin  22
#define mDrive1  7
#define mDrive2  6
#define potPin  A8
#define sdSelect  41
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY  2
#define ADAFRUITBLE_RST  9
#define redLED  31
#define YellLED  30
#define greenLED 32
#define line  49
#define button  3
#define echo  4
#define Trig  5
#define buzzer  40

Adafruit_BLE_UART uart = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);




void aciCallback(aci_evt_opcode_t event)
{
  Serial.println("Trying to start bluetooth");
  switch(event)
  {
    case ACI_EVT_DEVICE_STARTED:
      Serial.println(F("Advertising started"));
      break;
    case ACI_EVT_CONNECTED:
      Serial.println(F("Connected!"));
      break;
    case ACI_EVT_DISCONNECTED:
      Serial.println(F("Disconnected or advertising timed out"));
      break;
    default:
      break;
  }
}



void rxCallback(uint8_t *buffer, uint8_t len)
{
  Serial.print(F("Received "));
  Serial.print(len);
  Serial.print(F(" bytes: "));
  for(int i=0; i<len; i++)
   Serial.print((char)buffer[i]); 

  Serial.print(F(" ["));

  for(int i=0; i<len; i++)
  {
    Serial.print(" 0x"); Serial.print((char)buffer[i], HEX); 
  }
  Serial.println(F(" ]"));

  /* Echo the same data back! */
  uart.write(buffer, len);
}





void setup() {
  Serial.begin(9600);           // Open serial communications and wait for port to open:
  while (!Serial) {
    delay(1);                   // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(53, OUTPUT);
  pinMode(50, INPUT);
  pinMode(51, OUTPUT); 
 digitalWrite(ADAFRUITBLE_REQ, HIGH);
 digitalWrite(sdSelect, LOW);
 uart.setRXcallback(rxCallback);
 uart.setACIcallback(aciCallback);
 uart.setDeviceName("Dylan"); /* 7 characters max! */
 uart.begin();
 digitalWrite(ADAFRUITBLE_REQ, LOW);
 digitalWrite(sdSelect, HIGH);
// SD Card initialisation
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
  uart.pollACI();
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
