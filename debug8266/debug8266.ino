#include <SoftwareSerial.h>                        
SoftwareSerial esp8266serial(10,11);   
               
#define serialCommunicationSpeed 9600               
#define DEBUG true                                 

void setup()

{
  Serial.begin(serialCommunicationSpeed);           
  //esp8266.begin(serialCommunicationSpeed);     
  //InitWifiModule();                              
}


void loop() {
  // put your main code here, to run repeatedly:

}
