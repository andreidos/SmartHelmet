int  LED = 8;
int Button = 9;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Button, INPUT);

}

void loop() {
  int valoareButon = digitalRead(Button);

  if(valoareButon == 1){
    digitalWrite(LED, HIGH);
  }else{
  digitalWrite(LED, LOW);
  }

}
