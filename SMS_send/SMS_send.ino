#include <SoftwareSerial.h>

SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
String number = "+40754751679";

void setup() {
  delay(7000); //delay for 7 seconds to make sure the modules get the signal
  Serial.begin(9600);
  _buffer.reserve(50);
  Serial.println("Sistem Started...");
  sim.begin(9600);
  Serial.println("SIM begin");
  delay(1000);
  SendMessage();
}

void loop() {
  //SendMessage();
  delay(10000);
}

void SendMessage()
{
  Serial.println("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println("Setting SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "Hello, how are you?";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
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
    return sim.readString();
  }
}
