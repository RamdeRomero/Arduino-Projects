// C++ code
//
int redPin= 11;      // set red pin on LED to connect to pin 11 
int greenPin = 6;    // set green pin on LED to connect to pin 11
int bluePin = 5;      // set blue pin on LED to connect to pin 11


int button[] = {1,2,3};     // set or connect the buttons to individual pin 1-3
int buttonCount = 3;    // declare and initialize value of 3
int buttonState[] = {1,2,3};  // declare and initialize buttonstate as array and initialize values
                
void setup() {
  pinMode(redPin, OUTPUT);    // Define red pin as an output
  pinMode(greenPin, OUTPUT);    // Define green pin as an output
  pinMode(bluePin, OUTPUT);   // Define blue pin as an output
  for(int x=0; x<buttonCount; x++){         //creates a loop when condition is met
    pinMode(button[x], INPUT);  // Define each button as an input
  }
  
}
void loop() {   
  for(int x=0; x<buttonCount; x++){     //creates a loop when condition is met
    buttonState[x] = digitalRead(button[x]);    // Reads the state of the button
  }  
    if (buttonState[0] == HIGH) { // checks the condition id true or false
    // do stuff if the condition is true
        setColor(255, 0, 0); // Red Color // Set RGB led brightness of red to 255

    } else if (buttonState[1] == HIGH) {  // checks the condition id true or false
      // do stuff only if the first condition is false
      // and the second condition is true   
  setColor(0, 255, 0); // Green Color // Set RGB led brightness of green to 255
    } else if (buttonState[2] == HIGH) {    // checks the condition id true or false
      // do stuff only if the first condition is false
      // and the second condition is true
  setColor(0, 0, 255); // Blue Color  // Set RGB led brightness of blue to 255
    } else {
      setColor(170, 0, 255); // Purple Color  // Set RGB LED blue and red brightness to create a purple color
    }
 

}
void setColor(int redValue, int greenValue, int blueValue) {  //new function to return PWM signals 
  analogWrite(redPin, redValue);  // will represent the value of brightness of red LED
  analogWrite(greenPin, greenValue);  // will represent the value of brightness of green LED
  analogWrite(bluePin, blueValue);  // will represent the value of brightness of blue LED
}
