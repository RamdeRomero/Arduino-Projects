int trigPin = 12;    // Trigger
int echoPin = 11;    // Echo
long duration, cm, inches;
//Set the LED light to pin 8
int LED1 = 8;
int LED2 = 9;
//Set the float sensor to pin 3
#define Float_Switch2 6
#define Float_Switch 7
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  pinMode(Float_Switch, INPUT_PULLUP);
  pinMode(Float_Switch2, INPUT_PULLUP);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(2000);

  

  if(digitalRead(Float_Switch) == HIGH && digitalRead(Float_Switch2) == HIGH ) 
  {
    digitalWrite(LED1, HIGH); //Turn LED on
    if(cm<=50  ){
      Serial.println("The bin is full");
      digitalWrite(LED2, HIGH);
      
    }
    else if((cm>50) && (cm<60)){
      Serial.println("The bin is 70% ");
      digitalWrite(LED2, LOW);
      
    }
    else{
      digitalWrite(LED2, LOW);
    }
  }

 else
  {
    digitalWrite(LED1, LOW); //Turn LED off
  }

  
}
