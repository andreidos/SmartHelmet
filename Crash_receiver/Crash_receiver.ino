#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Network SSID
const char* ssid = "AndroidAP";
const char* password = "12345678";

SoftwareSerial gpss(4, 3);  //gps serial

int vib_pin=7;  //vibration sensor pin
double lastLatitude = -1;
double lastLongitude = -1;
char receivedString[5];
const String HOST="http://192.168.43.217:5000";
IPAddress ipAddress;

TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  gpss.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(10);
 
  // Connect WiFi
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  ipAddress = WiFi.localIP();

  Serial.println("Connected");
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

}

void loop() {
  readGpsCoordinates();
  Serial.readBytes(receivedString, 5);
  if(strlen(receivedString)>0 && strcmp(receivedString, "HELP")==0){
    Serial.println(receivedString);
    Serial.println("longitude: " + String(lastLongitude));
    Serial.println("latitude: " + String(lastLatitude));
    sendHelpRequest();
    memset(receivedString, 0, sizeof(receivedString));
  }
}

void sendHelpRequest() {
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    String payload = "";
    while(payload != "OK"){
      StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
      JsonObject& JSONencoder = JSONbuffer.createObject();
    
      JSONencoder["boardid"] = "WEMOS";
      JSONencoder["ipAddress"] = ipAddress.toString();
      JSONencoder["longitude"] = lastLongitude;
      JSONencoder["latitude"] = lastLatitude;
      char JSONmessageBuffer[300];
      JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    
      HTTPClient http;    //Declare object of class HTTPClient
    
      http.begin(HOST+"/api/locations/add");      //Specify request destination
      http.addHeader("Content-Type", "application/json");  //Specify content-type header
    
      int httpCode = http.POST(JSONmessageBuffer);   //Send the request
      payload = http.getString();  
      delay(5000);
    }
    payloadReceivedBlink();
  }
}

void readGpsCoordinates(){
  if(gpss.available() > 0){  
    gps.encode(gpss.read());    //decode the data from the GPS module
    if(gps.location.isUpdated()){  //if the location changed then we'll update the current location.
      lastLatitude = gps.location.lat();
      lastLongitude = gps.location.lng();
    }
  }
}

void payloadReceivedBlink(){
  for(int i=0;i<5;++i){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}

