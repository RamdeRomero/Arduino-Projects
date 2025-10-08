//Set the LED light to pin 8
int LED = 8;

//Set the float sensor to pin 3
#define Float_Switch2 7

void setup() {

  Serial.begin (9600);
  // initialize digital pin 8 as an output.
  pinMode(LED, OUTPUT);

 
  pinMode(Float_Switch2, INPUT_PULLUP);
}

void loop() {
 
 if(digitalRead(Float_Switch2) == HIGH)
  {
    digitalWrite(LED, HIGH); //Turn LED on
    Serial.println("high ");
  }

 else
  {
    digitalWrite(LED, LOW); //Turn LED off
    Serial.println("low ");
  }
}
