#include <Sim800l.h>
#include <SoftwareSerial.h>
Sim800l Sim800l;  //declare the library
char* text;
char* number;
bool error;


void setup(){
  Sim800l.begin();
  text="Testing Sms";
  number="+63673973113";
  error=Sim800l.sendSms(number,text);
  // OR
  //error=Sim800l.sendSms("+540111111111","the text go here");
}

void loop(){
  //do nothing
}
    
