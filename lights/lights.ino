int Lumina = 0;
int LEDV = 7;
int LEDG = 8;
int LEDR = 9;
int LEDs = 3;
int maxAnalogRead = 1023;

void setup() {
  pinMode(LEDV, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDR, OUTPUT);

}

void loop() {
  int valoareIluminare = analogRead(Lumina);
  int interval = maxAnalogRead / LEDs;

  digitalWrite(LEDV, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDR, LOW);

  int led = valoareIluminare / interval;

  switch(led){
    case 0:
    digitalWrite(LEDV, HIGH);
    break;
    case 1:
    digitalWrite(LEDG, HIGH);
    break;
    case 2:
    digitalWrite(LEDR, HIGH);
    break;
  }
}
