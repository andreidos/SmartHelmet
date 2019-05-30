#include <SoftwareSerial.h>
#include <TinyGPS++.h>    //https://github.com/mikalhart/TinyGPSPlus/releases

SoftwareSerial sim(11, 10); // RX, TX //SIM serial
SoftwareSerial gpss(4, 3);  //gps serial

static const uint32_t GPSBaud = 9600;
int vib_pin=7;  //vibration sensor pin
int _timeout;
String number = "+40754751679";
String _buffer;

double lastLatitude = -1;
double lastLongitude = -1;

TinyGPSPlus gps;    //TinyGPSPlus is a class used to ease the reading of data from the GPS module

void setup()  
{
  delay(7000); //delay for 7 seconds to make sure the modules get the signal
  Serial.begin(9600);
  pinMode(vib_pin,INPUT);
  sim.begin(9600);
  gpss.begin(GPSBaud);
  delay(1000);

}

void loop() {
   if(gpss.available() > 0){  
    gps.encode(gpss.read());    //decode the data from the GPS module
    if (gps.location.isUpdated()){  //if the location changed then we'll update the current location.
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);

      //in case the GPS module loses signal, we will send the last known location.
      lastLatitude = gps.location.lat();
      lastLongitude = gps.location.lng();
    }
  }
  
  long measurement =TP_init();    //get the vibration strength
  Serial.println("Shock value: " + String(measurement, 7));
  if(measurement>1000){     //if the vibration strength is high enough, send a message and exit. 
    SendMessage();
      exit(0);
  }
}

void SendMessage()
{
  String SMS = "Crash detected at location:\nLatitude: " + String(lastLatitude, 6) + "\nLongitude: " + String(lastLongitude,6);   //SMS message to be send
  Serial.println(SMS);
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  sim.println(SMS);   //send the SMS message to the GSM module
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z, used to mark the ending of a message
  delay(1000);
  _buffer = _readSerial();
}

String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();    //check if the module managed to send the message, should return an "OK" text or "ERROR" otherwise.
  }
}

long TP_init(){
  long measurement=pulseIn (vib_pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}
