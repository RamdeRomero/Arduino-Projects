//
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLt-wRO4_J"
#define BLYNK_DEVICE_NAME "4LED"
// This is the blynk auth token
#define BLYNK_AUTH_TOKEN "yxHi52dfibViUSrKJEGc6lcdK7cikppf"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "PLDTHOMEFIBRr8dGV";//Enter your WIFI name
char pass[] = "Romerofam#123";//Enter your WIFI password
//char ssid[] = "CCSE-306";
//char pass[] = "#LormaCCSE";

BlynkTimer timer;

//Get the button value
BLYNK_WRITE(V0)
{
  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(D0, OUTPUT);
  Blynk.begin(auth,ssid,pass, "blynk.cloud", 80);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run(); //Run the blynk library
}
