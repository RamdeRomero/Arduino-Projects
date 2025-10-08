// defines pins numbers

const int trigPin = D7;  //D4
const int echoPin = D6;  //D3
const int ledPin = D1;
const int ledPin2 = D2;
const int Buzzer = D0;
const int ldrPin = A0;

// defines variables
long duration;
int distance;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(ledPin, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(Buzzer, OUTPUT);
pinMode(ldrPin, INPUT);
Serial.begin(9600); // Starts the serial communication
}

void loop() {

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(2000);


int ldrStatus = analogRead(ldrPin);
Serial.print(ldrStatus);
  if (ldrStatus <=300) {

    digitalWrite(ledPin, HIGH);
    Serial.println("LDR is DARK, LED is ON");

  }
  if( (ldrStatus <=300) && (distance < 50)){
    tone(Buzzer, 6000);
    delay(2000);
    noTone(Buzzer);
    digitalWrite(ledPin2, HIGH);

    Serial.println("movement");
    
  }
  if ( (ldrStatus <=300) && (distance > 50)){
    digitalWrite(ledPin2, LOW);
    noTone(Buzzer);
  }
  else if(ldrStatus >300) {

    digitalWrite(ledPin, LOW);
    digitalWrite(Buzzer, LOW);
    Serial.println("LED is OFF");


  }
}
