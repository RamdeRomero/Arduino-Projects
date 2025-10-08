// C++ code

//Set LED for corresponding pin
int l1 = 3;
int l2 = 5;
int l3 = 6;
int l4 = 9;
int l5 = 10;
//Set button to a pin
int b1 = 12;
int b2 = 11;
// initialiaze button state
int bstate1 = 0;
int bstate2 = 0;

void setup()
{ 
  //initialiaze LED as output
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);
  pinMode(l5, OUTPUT);
  //initialize Button as input
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
}

void loop()
{
  bstate1 = digitalRead(b1);
  bstate2 = digitalRead(b2);
  if(bstate1 == HIGH){
    //intersecting LEDs 0.5 sec interval
    
   
    //outer layer
    digitalWrite(l1, HIGH);
    digitalWrite(l5, HIGH);
    delay(500); 
    digitalWrite(l1, LOW);
    digitalWrite(l5, LOW);
    delay(500);
     //2nd layer
    digitalWrite(l2, HIGH);
    digitalWrite(l4, HIGH);
    delay(500); 
    digitalWrite(l2, LOW);
    digitalWrite(l4, LOW);
    delay(500); 
    //mid
    digitalWrite(l3, HIGH);
    delay(500); 
    digitalWrite(l3, LOW);
    delay(500);


  }
  if(bstate2 == HIGH){  
    //Blinking LED
    //on
    digitalWrite(l5, HIGH); 
    digitalWrite(l4, HIGH);
    digitalWrite(l3, HIGH); 
    digitalWrite(l2, HIGH);
    digitalWrite(l1, HIGH); 
    delay(500); 
  //off
    
    digitalWrite(l1, LOW);
    digitalWrite(l5, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(l3, LOW);
    digitalWrite(l4, LOW);
    delay(500); 
  }
  else{
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(l3, LOW);
    digitalWrite(l4, LOW);
    digitalWrite(l5, LOW);
  }
}
