// C++ code

//button
int led = 12;    //set connect LED to pin 3
int b = 13;   //set push button to pin 12
int bstate;   //initialize button variable

//motor
const int enable = 6 ; //initializing pin 2 as enable
const int in_1 = 8 ;
const int in_2 = 9 ;
const int in_3 = 5 ;
const int in_4 = 7 ;
//sensor
const int trigger = 2;
const int echo = 3;

void setup()
{
  //set input/output
  pinMode(led, OUTPUT);   // define led as output
  pinMode(b, INPUT);      // define button as Input
  
  pinMode(enable,OUTPUT) ; //we have to set enable pin as output
  pinMode(in_1,OUTPUT) ; //Logic pins are also set as output
  pinMode(in_2,OUTPUT) ;
  pinMode(in_3,OUTPUT) ; 
  pinMode(in_4,OUTPUT) ;
  Serial.begin(9600);
 
}

void loop()
{ 
  //codes for sensor
   long duration,  cm;
   pinMode(trigger, OUTPUT);
   digitalWrite(trigger, LOW);
   delayMicroseconds(2);
   digitalWrite(trigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigger, LOW);
   pinMode(echo, INPUT);
   
  duration = pulseIn(echo, HIGH);
   cm = msToCm(duration);

   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(100);
  
  
  // A and B requirement
  bstate = digitalRead(b);
  if(bstate == 1){
     digitalWrite(led, HIGH);
     //clockwise
     digitalWrite(in_1,HIGH) ;
     digitalWrite(in_2,LOW) ;
     analogWrite(enable,255) ;
     delay(5000) ; // 5 secs
     //For brake
     digitalWrite(in_1,HIGH) ;
     digitalWrite(in_2,HIGH) ;
     delay(1000) ; // 1 sec
     //counter Clock-wise 
     digitalWrite(in_1,LOW) ;
     digitalWrite(in_2,HIGH) ;
     digitalWrite(in_3,LOW) ;
     digitalWrite(in_4,HIGH) ;
     delay(2000) ; // 2 secs
     //stop
     digitalWrite(in_1,HIGH) ;
     digitalWrite(in_2,HIGH) ;
     digitalWrite(in_3,HIGH) ;
     digitalWrite(in_4,HIGH) ;
     delay(2000) ; // 2 secs
    
  }
  else{
    digitalWrite(led, LOW);
    digitalWrite(in_1,HIGH) ;
    digitalWrite(in_2,HIGH) ;
    digitalWrite(in_3,HIGH) ;
    digitalWrite(in_4,HIGH) ;
    analogWrite(enable,255) ;
    if(cm > 25 ){
      //clockwise 1
       digitalWrite(in_1,HIGH) ;
       digitalWrite(in_2,LOW) ;
       
      delay(100);
    }
    else{
      //counter 1 and 2
     digitalWrite(in_1,LOW) ;
     digitalWrite(in_2,HIGH) ;
     digitalWrite(in_3,LOW) ;
     digitalWrite(in_4,HIGH) ;
     delay(200) ;
    }
    delay(100);
  }
  
}

long msToCm(long microseconds) {
   return microseconds / 29 / 2;
}
