int l1 = 3;   //set the LED to pin 3
int l2 = 5;   //set the LED to pin 5
int l3 = 6;   //set the LED to pin 6
int l4 = 9;   //set the LED to pin 9
int l5 = 10;  //set the LED to pin 10

int b1 = 11;  //set or connect the b1 to pin 11 
int b2 = 12;  //set or connect the b1 to pin 12

int currentStateB1; // Initialize and set value to default      
int currentStateB2; // Initialize and set value to default 
int lastStateB1 = LOW;  // intialize and set to Low
int lastStateB2 = LOW;   // intialize and set to Low
int debounceDelay = 500; // initialize and set value to 500

long debounceTimeB1 = 0;  // initialize the variable and set the value to zero
long debounceTimeB2 = 0;  // initialize the variable and set the value to zero


void setup() {
  // put your setup code here, to run once:
  // set and define the to corresponding input or output
  pinMode(l1, OUTPUT);  // we define the LED as an output
  pinMode(l2, OUTPUT);  // we define the LED as an output
  pinMode(l3, OUTPUT);  // we define the LED as an output
  pinMode(l4, OUTPUT);  // we define the LED as an output
  pinMode(l5, OUTPUT);  // we define the LED as an output
  pinMode(b1, INPUT);   //we define the button as an input
  pinMode(b2, INPUT);   //we define the button as an input

}

void loop() {
  // put your main code here, to run repeatedly:
  currentStateB1 = digitalRead(b1); // Read the value of b1 and insert it to currentStateB1 variable
  currentStateB2 = digitalRead(b2); // Read the value of b2 and insert it to currentStateB2 variable
  // debounce button1
  if( currentStateB1 != lastStateB1){ // check if currentStateB1 is not equal to lastStateB1
    debounceTimeB1 = millis();  // gets the millis function(program time running)
  }
  // press check and sequence
           
  if((millis() - debounceTimeB1) > debounceDelay){   // check if the time programrun(millis) minus the button is pressed(debouncetimeb1) is greater than debounceDelay=50)
    if(currentStateB1 == HIGH){
      //LED sequence 1
      // LED on l to r
      digitalWrite(l5, HIGH); // set the LED on
      delay(100);             // 100 msec interval
      digitalWrite(l4, HIGH);// set the LED on
      delay(100);// 100 msec interval
      digitalWrite(l3, HIGH);// set the LED on
      delay(100);// 100 msec interval
      digitalWrite(l2, HIGH);// set the LED on
      delay(100);// 100 msec interval
      digitalWrite(l1, HIGH);// set the LED on
      delay(100);   // 100 msec interval
      // LED off r to l
      digitalWrite(l1, LOW);  // LED will turn off
      delay(100);// 100 msec interval
      digitalWrite(l2, LOW);// LED will turn off
      delay(100);// 100 msec interval
      digitalWrite(l3, LOW);// LED will turn off
      delay(100);// 100 msec interval
      digitalWrite(l4, LOW);// LED will turn off
      delay(100);// 100 msec interval
      digitalWrite(l5, LOW);// LED will turn off
      // LED on r to l
      digitalWrite(l1, HIGH);// set the LED on
      delay(100);// 100 msec interval
      digitalWrite(l2, HIGH);// set the LED on
      delay(100);// 100 msec interval
      digitalWrite(l3, HIGH);// set the LED on
      delay(100);// 100 msec interval
      digitalWrite(l4, HIGH);// set the LED on
      delay(100);// 100 msec interval
      digitalWrite(l5, HIGH);// set the LED on
      delay(100); // 100 msec interval
      // LED off l to r
      digitalWrite(l5, LOW);// LED will turn off
      delay(100);// 100 msec interval
      digitalWrite(l4, LOW);// LED will turn off
      delay(100);// 100 msec interval
      digitalWrite(l3, LOW);// LED will turn off
      delay(100);// 100 msec interval
      digitalWrite(l2, LOW);// LED will turn off
      delay(100);// 100 msec interval
      digitalWrite(l1, LOW);// LED will turn off
      delay(100);// 100 msec interval
    }
  }

  // debounce button 2
  if( currentStateB2 != lastStateB2){ // check if currentStateB2 is not equal to lastStateB2
    debounceTimeB2 = millis();  // gets the millis function(program time running)
  }
  // press check and sequence
  if((millis() - debounceTimeB2) > debounceDelay){  // check if the time programrun(millis) minus the button is pressed(debouncetimeb2) is greater than debounceDelay=50)
    if(currentStateB2 == HIGH){ // check is currentStateb2 is high or the button is on
      //SEQUENCE 2
      // odd even off and on
      // odd on
      digitalWrite(l1, HIGH); // LED will turn on
      digitalWrite(l3, HIGH); // LED will turn on
      digitalWrite(l5, HIGH); // LED will turn on
      delay(200);             // 200 msec inter
      // odd of while even on
      digitalWrite(l1, LOW);  // LED will turn off
      digitalWrite(l3, LOW);  // LED will turn off
      digitalWrite(l5, LOW);  // LED will turn off
      digitalWrite(l2, HIGH); // LED will turn on
      digitalWrite(l4, HIGH); // LED will turn on
      delay(200);
      // even off while odd
      digitalWrite(l2, LOW);  // LED will turn off
      digitalWrite(l4, LOW);  // LED will turn off
      
    }
  }
  lastStateB1 = currentStateB1; // update lastStateB1 to equalto currentStateB1
  lastStateB2 = currentStateB2; // update lastStateB2 to equalto currentStateB2

}
