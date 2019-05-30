int LED1 = 7;
int LED2 = 8;
int Button = 9;
int Count;

void setup() {
  Serial.begin(9600);
  pinMode(Button, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Count = 0;
}

void loop() {
  int valoareButton = digitalRead(Button);
  if(valoareButton==1){
    Count = Count % 4;
    Serial.println(Count);
    Serial.println(valoareButton);
    Serial.println();
    lightIt();
    delay(300);
    ++Count;
  }
}

void lightIt(){
  switch(Count){
    case 0: digitalWrite(LED1, HIGH);
    break;
    case 1: digitalWrite(LED2, HIGH);
            digitalWrite(LED1, LOW);
    break;
    case 2:
            digitalWrite(LED1, HIGH);
            break;
    case 3: digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);
            break;
  }
}


