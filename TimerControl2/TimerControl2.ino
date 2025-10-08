const int relayPin =  4;      // the number of the LED pin
//int relayState = HIGH; 
  
unsigned long previousMillis = 0;     // will store last time LED was updated

unsigned long period = 6000;  
unsigned long limit;  
unsigned long store; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
   pinMode(relayPin, OUTPUT);
   //digitalWrite(relayPin, relayState);
   digitalWrite(relayPin, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(6000);
  unsigned long currentMillis = millis();
  previousMillis = currentMillis;
  store = previousMillis - period;
   if(digitalRead(relayPin) == HIGH){
    
    limit = previousMillis + period;
    Serial.print("lm  ");Serial.println(limit);
    Serial.print("cm  ");Serial.println(currentMillis);
    Serial.print("pm  ");Serial.println(store);
    delay(3000);
    if(currentMillis>=limit){
      digitalWrite(relayPin, LOW);
    }

    
    
//    if (currentMillis - previousMillis >= period){
//      previousMillis = currentMillis;
//      //relayState = LOW;
//      digitalWrite(relayPin, LOW);
//      
//
//    }
//  }
//  else if(digitalRead(relayPin) == LOW){
//    delay(5000);
//    //relayState = HIGH;
//    digitalWrite(relayPin, HIGH);
  }
//  //digitalWrite(relayPin, relayState);
//  Serial.println(digitalRead(relayPin));
//  Serial.println(currentMillis);
//  Serial.println(previousMillis);

}
