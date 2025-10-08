// C++ code

//RGB
int redPin= 10;      // set red pin on LED to connect to pin 10 
int greenPin = 5;   // set green pin on LED to connect to pin 15
int bluePin = 3;    // set blue pin on LED to connect to pin 3
//potentiometer
int pot = A0;   //set the LED to pin A0
int potVal = 0;   //Initialize variable and set value to 0
//3 LED
int led[] = {11,12,13};  // Set the individual LED to connect from pins  11 to 13
int count = 3;      // declare variable count and initialize value as 3


void setup()
{
  //RGB
  pinMode(redPin, OUTPUT);    // Define red pin as an output
  pinMode(greenPin, OUTPUT);    // Define green pin as an output
  pinMode(bluePin, OUTPUT);   // Define blue pin as an output
  //Pot
  pinMode(pot, INPUT);      // we define the Potentiometer as an input
  Serial.begin(9600);     // initialize the serial monitor
  // 3 LED
  for(int x = 0; x < count; x++){  //  creates a loop when x is less than count then x will increase by 1
    pinMode(led[x], OUTPUT);    // Define each LED as output 
  }
}

void loop()
{  
  //Potentiometer
  potVal = analogRead(pot); // read the value of the potentiometer and define value in potVal
  // Shows the value on the serial monitor
  Serial.print("pot= ");    // Serial monitor strings
  Serial.println(potVal);   // Serial monitor value of potVal  

  //RGB
  if ((potVal >= 10) && (potVal <= 350)) {  // condition is true when the value greater than/= 10 and less than 350
    // applies codes below if potVal is between 10 to 350
        setColor(120, 60, 0); // Set RGB led brightness of red to 120 and green to 60 output yellow
        digitalWrite(led[0], HIGH);   // LED turns on
        digitalWrite(led[1], LOW);    //LED TURNS OFF
        digitalWrite(led[2], LOW);    //LED TURNS OFF
    
    } else if ((potVal >= 351) && (potVal <= 750)) {  // condition is true when the value greater than/= 351  and less than/= 750
      // applies codes below if potVal is between 351 to 750  
    setColor(0, 120, 120); // Set RGB led brightness of green to 120 and blue to 120 output cyan
        digitalWrite(led[0], LOW);  // LED turns OFF
        digitalWrite(led[1], HIGH); //LED TURNS ON
        digitalWrite(led[2], LOW);  //LED TURNS OFF
    } else if ((potVal >= 751) && (potVal <= 950)) { // condition is true when the value greater than/= 751  and less than/= 950
     // applies codes below if potVal is between 751 to 950
      // and the second condition is true
    setColor(120, 0, 120);   // Set RGB led brightness of red to 120 and blue to 120 output purple
        digitalWrite(led[0], LOW);  // LED turns OFF
        digitalWrite(led[1], LOW); //LED TURNS OFF
        digitalWrite(led[2], HIGH);  //LED TURNS ON
      } else if (potVal >= 951 ) {    // ondition is true when the value greater than/= 951
      // applies codes below if potVal is greater than or equal to 951
      setColor(255, 165, 0); // Set RGB led brightness of red to 255 and green 165 output yelloworangegreen
          delay(1000);
          setColor(250, 0, 250); // Set RGB led brightness of red to 255 and green 165 output indigo
          delay(500);
          setColor(0, 192, 203);  // Set RGB led brightness of red to 255 and green 165 output bluegreen
          delay(200);
          digitalWrite(led[0], LOW);  // LED turns OFF
          digitalWrite(led[1], LOW); //LED TURNS OFF
          digitalWrite(led[2], LOW);  //LED TURNS OFF
       
    } else { // condition for values 10 below for 1-9 are the remaining values
      setColor(0, 0, 0); // Set RGB LED brigthness to all zero values or OFF state
      digitalWrite(led[0], LOW);  // LED turns OFF
      digitalWrite(led[1], LOW); //LED TURNS OFF
      digitalWrite(led[2], LOW);  //LED TURNS OFF

    }
  

  
}

void setColor(int redValue, int greenValue, int blueValue) {  //new function to return PWM signals 
  analogWrite(redPin, redValue);  // will represent the value of brightness of red LED
  analogWrite(greenPin, greenValue);  // will represent the value of brightness of green LED
  analogWrite(bluePin, blueValue);  // will represent the value of brightness of green LED
}
