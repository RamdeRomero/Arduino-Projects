const int ledPin = D1;
const int Buzzer = D0;
const int ldrPin = A0;

void setup() {

Serial.begin(9600);

pinMode(ledPin, OUTPUT);
pinMode(Buzzer, OUTPUT);
pinMode(ldrPin, INPUT);

}

void loop() {

int ldrStatus = analogRead(ldrPin);
Serial.print(ldrStatus);
  if (ldrStatus <=300) {

  digitalWrite(ledPin, HIGH);
  digitalWrite(Buzzer, HIGH);
  Serial.println("LDR is DARK, LED is ON");

  }

  else if(ldrStatus >300) {

  digitalWrite(ledPin, LOW);
  digitalWrite(Buzzer, LOW);
  Serial.println("LED is OFF");


  }

}
