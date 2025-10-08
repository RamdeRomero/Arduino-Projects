
#include <ESP8266WiFi.h>

//const char* ssid="PLDTHOMEFIBRr8dGV";     //Declare ssid variable and input your Wifi SSID
//const char* password = "Romerofam#123";   //Declare password variable and input your Wifi password 
const char* ssid="CCSE-303";     //Declare ssid variable and input your Wifi SSID
const char* password = "#LormaCCSE";   //Declare password variable and input your Wifi password 

int ledPin = 13;    //Set ledPin variable to pin D7 

void setup() {
 
  pinMode(ledPin,OUTPUT);   // initialize LED as output 
  digitalWrite(ledPin,LOW); // Set the LED pin to light up

  Serial.begin(115200);     // initialize the serial monitor 
  Serial.println();           
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);  //Initializes the WiFi library’s network settings and provides the current status.

  Serial.println();
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){   //Return the connection status and checkk if it si not connected then it execute the code bellow
      delay(500);
      Serial.print(".");        
  }

  digitalWrite( ledPin , HIGH);   // Turn the LED on 
  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );   // Gets the WiFi shield’s IP address

}

void loop() {
  // put your main code here, to run repeatedly:

}
