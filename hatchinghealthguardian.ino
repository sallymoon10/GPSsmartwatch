// This code is for a GPS tracking smart watch that helps guide dementia patients safely home. 
// When the user presses the "Home" button or they go beyond safe boundaries, the GPS will detect the user's current 
// location and instructions on how to get home (eg. go left, go straight) through an LCD Display.

// Limitations include: 
// map api not implemented
// limited instructions for directions
// home boundaries not customizable by user
// not fully tested 

// This code was writted by a collaborative team at Hathching Health Hackathon 2016. 

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <stdio.h>
#include <LiquidCrystal.h>

// Direction Definition
#define stay      0
#define goUP      1
#define goDOWN    2
#define goLEFT    3
#define goRIGHT   4

//Set up LCD display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// GPS pin declaration
int RXPin = 2;
int TXPin = 3;

// The Skytaq EM-506 GPS module included in the GPS Shield Kit
// uses 4800 baud by default
int GPSBaud = 4800;


// The GPS object declaration
TinyGPSPlus GPS;

// The GPS serial port declaration
SoftwareSerial gpsSerial(RXPin, TXPin);

// Home boundaries set by user
double HomeLeftX = 49.262184;
double HomeRightX = 49.262214;
double HomeUpY = -123.248535;
double HomeDownY = -123.248611;

// Set boundary limit, when user gets past this boundary the watch will ask user if they wish to home. 
double OUTBOUND = -123.248680;
volatile int state;


void setup() {
  state = 1;
   // Start the Arduino hardware serial port at 9600 baud
  Serial.begin(9600);
  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);
}


void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0)
    if (GPS.encode(gpsSerial.read()))
     checkGPSLocation();

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && GPS.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected"));
    while(true);
  }
}
void checkGPSLocation() {

  if(GPS.location.lng() < OUTBOUND)
  {
    Serial.println("Hello dear, You seem to be going a little far. Would you like to go home?");
    int promt= userResponse();
    if (prompt== 1)
    {
      gpsState= cmpCurLoc();
      motionState= accelDetect();
      
      if (gpsState==1){
        Serial.println("GO BACKWARDS");
      }
      else if(gpsState == 2){
        Serial.println("GO STRAIGHT");
      }
      else if(gpsState == 3){
        Serial.println("GO LEFT");
      }
      else if(gpsState == 4){
        Serial.println("GO RIGHT");
      }
      delay(2000);
    }
  }

  gpsState = cmpCurLoc();
  motionState= accelDetect();

  if (state == 0 && motionState ==1)
  {
    lcd.display();
    lcd.clear();
    lcd.print("You're Home!");
    delay(5000);
  }
  else
  {
    gpsState= cmpCurLoc();
    
    if (gpsState==1){
      lcd.display();
      lcd.clear();
      lcd.print("Go back");
      delay(5000);
    }
    else if(gpsState == 2){
      lcd.display();
      lcd.clear();
      lcd.print("Go straight");
      delay(5000);
    }
    else if(gpsState == 3){
      lcd.display();
      lcd.clear();
      lcd.print("Turn left");
      delay(5000);
    }
    else if(gpsState == 4){
      lcd.display();
      lcd.clear();
      lcd.print("Turn right");
      delay(5000);
    }
    delay(2000);
  }


}



