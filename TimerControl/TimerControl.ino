

const int relayPin =  4;      // the number of the LED pin
//int relayState = HIGH; 
  
unsigned long previousMillis = 0;     // will store last time LED was updated

const long period = 3000;           // interval at which to blink (milliseconds)

void setup() { 
   Serial.begin(9600); 
   pinMode(relayPin, OUTPUT);
   //digitalWrite(relayPin, relayState);
   digitalWrite(relayPin, HIGH);
} 

void loop() { 
  
  
  
  unsigned long currentMillis = millis();
  
  if(digitalRead(relayPin) == HIGH){
    if(previousMillis != 0){
      previousMillis = currentMillis - previousMillis;
    }    
    
    if (currentMillis - previousMillis >= period){
      digitalWrite(relayPin, LOW);

      previousMillis = currentMillis;
      

    }
  }
  else if(digitalRead(relayPin) == LOW){
    delay(1000);
    //relayState = HIGH;
    digitalWrite(relayPin, HIGH);
  }
  
  //digitalWrite(relayPin, relayState);
  Serial.println(digitalRead(relayPin));
  Serial.println(currentMillis);
  Serial.println(previousMillis);
  delay(2000);
  
  
  
  
//  if (currentMillis - previousMillis >= interval) {
//    // save the last time you blinked the LED
//    previousMillis = currentMillis;
//
//    // if the LED is off turn it on and vice-versa:
//    if (ledState == LOW) {
//      ledState = HIGH;
//    } else {
//      ledState = LOW;
//    }
//
//    // set the LED with the ledState of the variable:
//    
  //}
}
