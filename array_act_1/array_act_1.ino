// C++ code

int led[] = {9,10,11,12,13};  // Set the individual LED to connect from pins  9 to 13
int count = 5;      // declare variable count and initialize value as 5

void setup()
{
  for(int x = 0; x < count; x++){ //  creates a loop when x is less than count then x will increase by 1
    pinMode(led[x], OUTPUT);    // Define each LED as output
  }  
}

void loop()
{
  for( int x = 0; x < count; x++){  // Creates a loop when x is less than count then x will increase by 1
    //on right to left    
    digitalWrite(led[x], HIGH); //  Turns on the LED of variable x when the condition above is met
    delay(500);     // a 500 milli second interval is applied
  }
  
  for( int x = 0; x < count; x++){
    //off
    digitalWrite(led[x], LOW);  //  Turns off the LED of variable x when the condition above is met
  }
  delay(500);     // a 500 milli second interval is applied
}
