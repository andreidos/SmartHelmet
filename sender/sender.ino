char mystr[5] = "Hello"; //String data

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(115200);
}

void loop() {
  Serial.write(mystr,5); //Write the serial data
  delay(1000);
}
