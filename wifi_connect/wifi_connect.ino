#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
// Network SSID
const char* ssid = "AndroidAP";
const char* password = "12345678";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); 
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(115200);
  delay(10);
 
  // Connect WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
 
void loop() {

  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& JSONencoder = JSONbuffer.createObject();
  
    JSONencoder["boardid"] = "ardu";
    JSONencoder["longitude"] = 123.00;
    JSONencoder["latitude"] = 123.00;
    JSONencoder["ipAddress"] = "0.0.0.0";
    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  
    HTTPClient http;    //Declare object of class HTTPClient
  
    http.begin("http://192.168.43.217:5000/api/locations/add");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
  
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                  //Get the response payload

    Serial.println("payload: " + payload);
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(30000);  //Send a request every 30 seconds
  
}
