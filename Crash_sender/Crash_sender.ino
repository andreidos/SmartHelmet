#include <SoftwareSerial.h>
#include <TinyGPS++.h>

int vib_pin=7;  //vibration sensor pin

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200);
}

void loop() {
  long shockMeasurement=getShockValue();
  if(shockMeasurement>1000){
    Serial.write("HELP");
    digitalWrite(LED_BUILTIN,HIGH);
    delay(10000);
    digitalWrite(LED_BUILTIN,LOW);
  }
}

long getShockValue(){
  long measurement=pulseIn (vib_pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}

