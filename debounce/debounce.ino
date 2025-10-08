// C++ code
//
int led = 3;    //set connect LED to pin 3
int b = 12;   //set push button to pin 12

int bstate;   //initialize button variable
int lastBstate =  LOW;  //set initial button state to off
int lstate =  LOW;  //set initial LED state to off

int lastDebounceTime = 0; //declare and set a value to the last debounce time in milliseconds
int debounceDelay = 50; //declare and set a value to the debounce delay in milliseconds

void setup()
{
  //set input/output
  pinMode(led, OUTPUT);   // define led as output
  pinMode(b, INPUT);      // define button as Input
  //set state
  digitalWrite(led, lstate);    //initialized the state of LED
}

void loop()
{ 
  int read = digitalRead(b);    //set new variable that reads the button
  
  if(read != lastBstate){     //check if read is not equal to lastBstate
   //reset debounce timer   
    lastDebounceTime = millis();    //gets the time of the time button is pressed and reset it
          //millis function return the number of milli secs that the sketch is running for
  }
  //check if button press is over 50 milsec
  if((millis() - lastDebounceTime) > debounceDelay){// check if millis minus lastDebounceTime is greeater than debounce Delay
    if(read != bstate){
  //update button state
      bstate = read;      // reads the button state
      if(bstate == HIGH){     // checks if bstate is high
        lstate = !lstate;     // have a toggle function for off and on
      }
    } 
  }
//set the LED
  digitalWrite(led, lstate);    //LED is on or off
// update last button state
  lastBstate = read;    // set  lastbutton state to read value
}
