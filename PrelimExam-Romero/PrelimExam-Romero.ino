
//Include the library files
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLFAY7Q8zW"
#define BLYNK_DEVICE_NAME "Prelim Exam  Romero"
#define BLYNK_AUTH_TOKEN "DZPlB1mv7M3aXq7AyJFIz4tRmnVFzP_a" 

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "PLDTHOMEFIBRr8dGV";//Enter your WIFI name
char pass[] = "Romerofam#123";//Enter your WIFI password
//char ssid[] = "CCSE-303";
//char pass[] = "#LormaCCSE";

BlynkTimer timer;

//Get the button value
BLYNK_WRITE(V0)
{
  
  if(param.asInt() == 1){
    // execute this code if the switch widget is now ON
    digitalWrite(D3,HIGH);  // Set digital pin HIGH
    delay(1000);
    digitalWrite(D2,HIGH);  // Set digital pin HIGH
    delay(1000);
    digitalWrite(D1,HIGH);  // Set digital pin HIGH
    delay(1000);
    digitalWrite(D0,HIGH);  // Set digital pin HIGH
    delay(1000);
  }
  else{
    digitalWrite(D3,LOW);  // Set digital pin HIGH
    delay(1000);
    digitalWrite(D2,LOW);  // Set digital pin LOW 
    delay(1000);
    digitalWrite(D1,LOW);  // Set digital pin HIGH
    delay(1000);
    digitalWrite(D0,LOW);  // Set digital pin LOW 
    delay(1000);
  }
  
}
BLYNK_WRITE(V1)
{
    if(param.asInt() == 1){
    // execute this code if the switch widget is now ON
    //3
    digitalWrite(D2,HIGH);  // Set digital pin HIGH
    delay(1000);
    //2
    digitalWrite(D1,HIGH);  // Set digital pin HIGH
    delay(1000);
    //4
    digitalWrite(D3,HIGH);  // Set digital pin HIGH
    delay(1000);
    
    //1
    digitalWrite(D0,HIGH);  // Set digital pin HIGH
    delay(1000);

  }
  else{
    
    digitalWrite(D2,LOW);  // Set digital pin HIGH
    delay(1000);
    digitalWrite(D1,LOW);  // Set digital pin LOW 
    delay(1000);
    digitalWrite(D3,LOW);  // Set digital pin HIGH
    delay(1000);
    digitalWrite(D0,LOW);  // Set digital pin LOW 
    delay(1000);
  }
}
BLYNK_WRITE(V2)
{
  if(param.asInt() == 1){
    // execute this code if the switch widget is now ON
    //3
    digitalWrite(D2,HIGH);  // Set digital pin HIGH
    //2
    digitalWrite(D1,HIGH);  // Set digital pin HIGH
    //4
    digitalWrite(D3,HIGH);  // Set digital pin HIGH
    //1
    digitalWrite(D0,HIGH);  // Set digital pin HIGH

  }
  else{
    
    digitalWrite(D2,LOW);  // Set digital pin HIGH
    digitalWrite(D1,LOW);  // Set digital pin LOW 
    digitalWrite(D3,LOW);  // Set digital pin HIGH
    digitalWrite(D0,LOW);  // Set digital pin LOW 
  }
}
BLYNK_WRITE(V3)
{
  if(param.asInt() == 1){
    // execute this code if the switch widget is now ON
    digitalWrite(D0,HIGH);  // Set digital pin HIGH
    delay(1000);
    digitalWrite(D3,HIGH);  // Set digital pin HIGH
    delay(2000);
    digitalWrite(D1,HIGH);  // Set digital pin HIGH
    delay(3000);
    digitalWrite(D2,HIGH);  // Set digital pin HIGH
    delay(1000);
  }
  else{
    digitalWrite(D0,LOW);  // Set digital pin HIGH
    delay(1000);
    digitalWrite(D3,LOW);  // Set digital pin LOW 
    delay(2000);
    digitalWrite(D1,LOW);  // Set digital pin HIGH
    delay(3000);
    digitalWrite(D2,LOW);  // Set digital pin LOW 
    delay(1000);
  }
}
void setup()
{
  //Set the LED pin as an output pin
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  //Initialize the Blyk library
  Blynk.begin(auth,ssid,pass, "blynk.cloud", 80);
}
void loop()
{
  Blynk.run(); //Run the blynk library
}
