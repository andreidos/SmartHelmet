char mystr[30]; //Initialized variable to store recieved data

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.readBytes(mystr,30); //Read the serial data and store in var
  if(strlen(mystr)>0){
    Serial.println(mystr); //Print data on Serial Monitor
    memset(mystr, 0, sizeof(mystr));
  }
}
