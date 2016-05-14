
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <stdlib.h>
#include <stdio.h>
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

// Home Corners
double HomeLeftX = 49.262184;
double HomeRightX = 49.262214;
double HomeUpY = -123.248535;
double HomeDownY = -123.248611;

// Direction Definition
#define stay      0
#define goUP      1
#define goDOWN    2
#define goLEFT    3
#define goRIGHT   4

void GPSsetup() {
  // Start the Arduino hardware serial port at 9600 baud
  Serial.begin(9600);

  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);
  Serial.print(F("Starting GPS\n")); 

}

int checkGPSAvail(void){
  // if the GPS is available
  if(gpsSerial.available() > 0){
    if(GPS.encode(gpsSerial.read())){
        return 1;   
    }
  }
  return 0;
}

int cmpCurLoc(void){
  double GPS_lat, GPS_log;
  if(checkGPSAvail()){
   while(!GPS.location.isValid()){
     Serial.print(F("GPS location is not valid, wait"));
    }
   
    GPS_lat = GPS.location.lat();
    GPS_log = GPS.location.lng();

   // If user location is at the left of home but within the up and down range of home
   if( GPS.location.lng() >= HomeDownY && GPS.location.lng() <= HomeUpY){
         if(GPS.location.lat() >= HomeLeftX && GPS.location.lat() <= HomeRightX){
          return 0; 
         }
         if(GPS.location.lat() < HomeRightX){
          return 1;
         }
         if(GPS.location.lat() > HomeLeftX){
          return 2;
         }
      
    }

    // If user location is at the bottom quardrant of home 
   else if(GPS.location.lng() < HomeDownY){
        return 3;
    }

    // If user location is at the top quardrant of home
   else if(GPS.location.lng() > HomeUpY){
        return 4;
    } 

  

}



