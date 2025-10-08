int l1 = 3;   // set the LED connection to pin 3
int l2 = 5;   // set the LED connection to pin 5
int l3 = 6;   // set the LED connection to pin 6
int l4 = 9;   // set the LED connection to pin 9
int l5 = 10;  // set the LED connection to pin 10

int b1 = 11; // set button to pin 11
int b2 = 12; // set button to pin 12 

int currentStateB1; //initialize and set the value to default 
int currentStateB2; //initialize and set the value to default 
int lastStateB1 = LOW;  //initialize and set the value to LOW
int lastStateB2 = LOW;  //initialize and set the value to LOW
int debounceDelay = 500; // intialize the variabe and set it to value 500

long debounceTime1 = 0;
long debounceTime2 = 0;

void setup() {
  // put your setup code here, to run once:
  // Initialize set the components as an input or output
  pinMode(l1, OUTPUT);  // define the LED as an output
  pinMode(l2, OUTPUT);  // define the LED as an output
  pinMode(l3, OUTPUT);  // define the LED as an output
  pinMode(l4, OUTPUT);  // define the LED as an output
  pinMode(l5, OUTPUT);  // define the LED as an output
  pinMode(b1, INPUT);   // define the button as an input
  pinMode(b2, INPUT);   // define the button as an input

}

void loop() {
  // put your main code here, to run repeatedly:
  currentStateB1 = digitalRead(b1);  // read the state of the button H OR L
  currentStateB2 = digitalRead(b2);  // read the state of the button H OR L

  if(currentStateB1 != lastStateB1){    // will check if currentStateB1 is not equal to lastStateB1
    debounceTime1 = millis();            // will get the time the program is running
  }
  if((millis() - debounceTime1) > debounceDelay){ // check if the quantity runningtime minus timepressed if it is greater that 50 milli secods 
    if(currentStateB1 == HIGH){           // check currentState if is it equal to High
      //left to rign on
      digitalWrite(l5, HIGH); // LED will turn on
      delay(100);             // 100 milli seconds interval
      digitalWrite(l4, HIGH); // LED will turn on
      delay(100);             // 100 milli seconds interval
      digitalWrite(l3, HIGH); // LED will turn on
      delay(100);             // 100 milli seconds interval
      digitalWrite(l2, HIGH); // LED will turn on
      delay(100);             // 100 milli seconds interval
      digitalWrite(l1, HIGH); // LED will turn on
      delay(100);             // 100 milli seconds interval
      //right to left off
      digitalWrite(l1, LOW);  // LED will turn off
      delay(100);             // 100 milli seconds interval
      digitalWrite(l2, LOW);  // LED will turn off
      delay(100);             // 100 milli seconds interval
      digitalWrite(l3, LOW);  // LED will turn off
      delay(100);             // 100 milli seconds interval
      digitalWrite(l4, LOW);  // LED will turn off
      delay(100);             // 100 milli seconds interval
      digitalWrite(l5, LOW);  // LED will turn off
      //rigt to left on
      digitalWrite(l1, HIGH); // LED will turn on
      delay(100); //100 milli seconds interval
      digitalWrite(l2, HIGH); // LED will turn on
      delay(100); //100 milli seconds interval
      digitalWrite(l3, HIGH); // LED will turn on
      delay(100); //100 milli seconds interval
      digitalWrite(l4, HIGH); // LED will turn on
      delay(100); //100 milli seconds interval
      digitalWrite(l5, HIGH); // LED will turn on
      delay(100); //100 milli seconds interval
      //left to rigth off
      digitalWrite(l5, LOW);  // LED will turn off
      delay(100); //100 milli seconds interval
      digitalWrite(l4, LOW);  // LED will turn off
      delay(100); //100 milli seconds interval
      digitalWrite(l3, LOW);  // LED will turn off
      delay(100); //100 milli seconds interval
      digitalWrite(l2, LOW);  // LED will turn off
      delay(100); //100 milli seconds interval
      digitalWrite(l1, LOW);  // LED will turn off
      
    }
  }
  if(currentStateB2 != lastStateB2){    // will check if currentStateB1 is not equal to lastStateB2
    debounceTime2 = millis();            // will get the time the program is running
  }
  if((millis() - debounceTime2) > debounceDelay){  // check if the quantity runningtime minus timepressed if it is greater that 50 milli secods 
    if(currentStateB2 == HIGH){           // check currentState if is it equal to High
      //odd and even lighting
      //odd on
      digitalWrite(l1, HIGH);     // LED will turn on
      digitalWrite(l3, HIGH);   // LED will turn on
      digitalWrite(l5, HIGH);   // LED will turn on
      delay(200);               //200 milli seconds interval
      //odd off
      digitalWrite(l1, LOW);    // LED will turn off
      digitalWrite(l3, LOW);    // LED will turn off
      digitalWrite(l5, LOW);    // LED will turn off
      //even will turn on
      digitalWrite(l2, HIGH);   // LED will turn on
      digitalWrite(l4, HIGH);    // LED will turn on
      delay(200);               //200 milli seconds interval
      //even turn off
      digitalWrite(l2, LOW);    // LED will turn off
      digitalWrite(l4, LOW);    // LED will turn off

    }
  }
  lastStateB1 = currentStateB1;   //update the lastestate using the current state
  lastStateB2 = currentStateB2;   //update the lastestate using the current state
}
