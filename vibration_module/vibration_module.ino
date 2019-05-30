int vibr_Pin = 7 ;

void setup(){
  pinMode(vibr_Pin, INPUT); //set vibr_Pin input for measurment
  Serial.begin(9600); //init serial 9600
}
void loop(){
  long measurement =TP_init();
  delay(50);
  Serial.println(measurement);
  if (measurement > 100000){
      Serial.println("SHOCK DETECTED");
  }
}
long TP_init(){
  delay(10);
  long measurement=pulseIn (vibr_Pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}
