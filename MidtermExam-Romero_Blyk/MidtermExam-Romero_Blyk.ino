
//Include the library files
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLriqdtz-I"
#define BLYNK_DEVICE_NAME "MidtermNodeMCU"
#define BLYNK_AUTH_TOKEN "Q6f3xX_X1_r0klMakdy-t9Ni7C3540c_"

char auth[] = BLYNK_AUTH_TOKEN;
//char ssid[] = "PLDTHOMEFIBRr8dGV";//Enter your WIFI name
//char pass[] = "Romerofam#123";//Enter your WIFI password
char ssid[] = "CCSE-304";
char pass[] = "#LormaCCSE";

BlynkTimer timer;

// defines pins numbers
int pinValue = 0;
const int trigPin = D7;  //D4
const int echoPin = D6;  //D3
const int ledPin = D1;
const int ledPin2 = D2;
const int Buzzer = D0;
const int ldrPin = A0;

// defines variables
long duration;
int distance;
BLYNK_WRITE(V0)
{
 if(param.asInt() == 1){ 
    digitalWrite(ledPin2, HIGH);
  }
  else if(param.asInt() == 1){
    digitalWrite(ledPin2, LOW);
    
  }
  
}
BLYNK_WRITE(V1)
{
  if(param.asInt() == 1){ 
    digitalWrite(Buzzer, HIGH);
    delay(3000);
    digitalWrite(Buzzer, LOW);
  }
  else{
    
    
  }
}




//////////////////////////////////////////////////////////////////////////////////////////



void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(ledPin, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(Buzzer, OUTPUT);
pinMode(ldrPin, INPUT);
Serial.begin(9600); // Starts the serial communication
Blynk.begin(auth,ssid,pass, "blynk.cloud", 80);
}

void loop() {

  Blynk.run(); //Run the blynk library
  timer.run();

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(2000);
  
  
  int ldrStatus = analogRead(ldrPin);
  Serial.print(ldrStatus);
    if (ldrStatus <=300) {
  
      digitalWrite(ledPin, HIGH);
      Serial.println("LDR is DARK, LED is ON");
  
    }
    if( (ldrStatus <=300) && (distance < 50)){
      digitalWrite(Buzzer, HIGH);
      delay(3000);
      digitalWrite(Buzzer, LOW);
      digitalWrite(ledPin2, HIGH);
      Blynk.logEvent("sonic","Detected object nearby");
      Serial.println("movement");
      
    }
    if ( (ldrStatus <=300) && (distance > 50)){
      digitalWrite(ledPin2, LOW);
      noTone(Buzzer);
    }
    else if(ldrStatus >300) {
  
      digitalWrite(ledPin, LOW);
      digitalWrite(ledPin2, LOW);
      digitalWrite(Buzzer, LOW);
      Serial.println("LED is OFF");
  
  
    }
    Blynk.virtualWrite(V2, ldrStatus);
    Blynk.virtualWrite(V3, distance);
  
    
}
