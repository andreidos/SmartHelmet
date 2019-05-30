#include <SoftwareSerial.h>

String Arsp, Grsp;
SoftwareSerial gsm(10, 11); // RX, TX

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Testing GSM SIM800L");
  gsm.begin(9600);
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(gsm.available())
  {
    Grsp = gsm.readString();
    Serial.println(Grsp);
  }

  if(Serial.available())
  {
    Arsp = Serial.readString();
    if(Arsp=="send msg"){
      SendTextMessage();
    }else{
      gsm.println(Arsp);
    }
  }
}

void SendMessage()
{
  Serial.println("Sending Message");
  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(3000);
  gsm.println("AT+CEER=1");
  delay(3000);
  Serial.println("Setting SMS Number");
  String number = "+40754751679";
  gsm.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(3000);
  String SMS = "Hello, how are you?";
  gsm.println(SMS);
  delay(3000);
  gsm.println((char)26);// ASCII code of CTRL+Z
  delay(3000);
}

void SendTextMessage(){
  gsm.write("AT+CMGF=1\r\n");
  delay(1000); 
  gsm.write("AT+CMGS=\"+40754751679\"\r\n");
  delay(1000);
  gsm.write("Test");
  delay(1000);   
  gsm.write((char)26);
  delay(2000);
  Serial.println("message should have beeen sent");
  }
