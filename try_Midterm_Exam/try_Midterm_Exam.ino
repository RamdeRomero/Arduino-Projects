// C++ code 

int b1 = 11;
int b2 = 12;

int l1 = 3;
int l2 = 5;
int l3 = 6;
int l4 = 9;
int l5 = 10;

int debounceDelay = 500;
int lastStateB1   = LOW;
int currentStateB1;
int lastStateB2 = LOW;
int currentStateB2;

unsigned long lastDebounceTime = 0;
unsigned long lastDebounceTime2 = 0;


void setup(){
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT); 
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);
  pinMode(l5, OUTPUT);
}

void loop(){
 currentStateB1 = digitalRead(b1);
 currentStateB2 = digitalRead(b2);
  //b1 debounce
  //read the time when button is pressed
  if (currentStateB1 != lastStateB1){
    lastDebounceTime = millis();  //gets the program is running while being pressed
      
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if( currentStateB1 == HIGH){
        
        // on  r to l
        digitalWrite(l5, HIGH);
        delay(100);
        digitalWrite(l4, HIGH);
        delay(100);
        digitalWrite(l3, HIGH);
        delay(100);
        digitalWrite(l2, HIGH);
        delay(100);
        digitalWrite(l1, HIGH);
        delay(100);
      
        //off r to l

        digitalWrite(l1, LOW);
        delay(100);
        digitalWrite(l2, LOW);
        delay(100);
        digitalWrite(l3, LOW);
        delay(100);
        digitalWrite(l4, LOW);
        delay(100);
        digitalWrite(l5, LOW);
        
      //on  l to r
        digitalWrite(l1, HIGH);
        delay(100);
        digitalWrite(l2, HIGH);
        delay(100);
        digitalWrite(l3, HIGH);
        delay(100);
        digitalWrite(l4, HIGH);
        delay(100);
        digitalWrite(l5, HIGH);
        delay(100);
      
        //off l to r

        digitalWrite(l5, LOW);
        delay(200);
        digitalWrite(l4, LOW);
        delay(200);
        digitalWrite(l3, LOW);
        delay(200);
        digitalWrite(l2, LOW);
        delay(200);
        digitalWrite(l1, LOW);
        
      
        
    }
  }
  //b2 debounce
  //b2 debounce
  if (currentStateB2 != lastStateB2){
   lastDebounceTime2 = millis();
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if( currentStateB2 == HIGH){
     //intersecting LEDs 0.5 sec interval
      // odd
        digitalWrite(l2, HIGH);
        digitalWrite(l4, HIGH);        
        delay(300); 
        digitalWrite(l2, LOW);
        digitalWrite(l4, LOW);        
        delay(300);
        // even
        digitalWrite(l1, HIGH);
        digitalWrite(l3, HIGH);
        digitalWrite(l5, HIGH);
        delay(300); 
        digitalWrite(l1, LOW);
        digitalWrite(l5, LOW);
        digitalWrite(l3, LOW);
        delay(300);
          
      
      
    }
  }
      
  lastStateB1 = currentStateB1; 
  lastStateB2 = currentStateB2;
}
  
