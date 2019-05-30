#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial gpss(4, 3);  //gps serial

int vib_pin=7;  //vibration sensor pin
double lastLatitude = -1;
double lastLongitude = -1;

TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  gpss.begin(9600);
}

void loop() {
  readGpsCoordinates();
  long shockMeasurement=getShockValue();
  //Serial.println(shockMeasurement);
  if(shockMeasurement>1000){
    String lastLocation = String(lastLongitude,6) + " " + String(lastLatitude,6);
    char locationCharArray[30];
    lastLocation.toCharArray(locationCharArray, lastLocation.length());
    Serial.write(locationCharArray);
    delay(5000);
  }
}

void readGpsCoordinates(){
  if(gpss.available() > 0){  
    gps.encode(gpss.read());    //decode the data from the GPS module
    if(gps.location.isUpdated()){  //if the location changed then we'll update the current location.
      //Serial.print("Latitude= "); 
      //Serial.print(gps.location.lat(), 6);
      //Serial.print(" Longitude= "); 
      //Serial.println(gps.location.lng(), 6);

      //in case the GPS module loses signal, we will send the last known location.
      lastLatitude = gps.location.lat();
      lastLongitude = gps.location.lng();
    }
  }
}

long getShockValue(){
  long measurement=pulseIn (vib_pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}

