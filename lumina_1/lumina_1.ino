int Lumina = 0;

void setup() {
  Serial.begin(9600);
}


void loop() {
  int valoareIluminare = analogRead(Lumina);
  Serial.println(valoareIluminare, DEC);
  delay(10);
}

