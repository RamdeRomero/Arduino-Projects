int trigPin = 12;    // Trigger
int echoPin = 11;    // Echo
long duration, cm, inches;
//Set the LED light to pin 8
int LED1 = 8;
int LED2 = 9;
int y1 = 1; 
int y2 = 1; 
//Set the float sensor to pin 3
#define Float_Switch 6
#define Float_Switch2 7
//Gsm library 

//Gsm //  Gsm  Gsm  Gsm  Gsm 
#include <SoftwareSerial.h>
//GSM Module TX is connected to Arduino D8
#define SIM800_TX_PIN 3
//GSM Module RX is connected to Arduino D9
#define SIM800_RX_PIN 2 
SoftwareSerial mySerial(SIM800_TX_PIN, SIM800_RX_PIN); //Create software serial object to communicate with GSM Module

int device_1 = 13; // attach pin D13 of Arduino to Device-1
int relayPin = 4; // attach pin D12 of Arduino to Relay 
// defines variables for GSM
int index = 0;
String number = "";
String message = "";
char incomingByte;
String incomingData;
bool atCommand = true;

//Rtc
//RTC
// DS1302:  CE pin    -> Arduino Digital 2 -5
//          I/O pin   -> Arduino Digital 3 - 9
//          SCLK pin  -> Arduino Digital 4 - 10
#include <DS1302.h>
DS1302 rtc(5, 9, 10);
Time t;
byte OnHour   = 9;
byte OnMin    = 0;
byte OffHour  = 9;
byte OffMin   = 1;

//for millis
//int relayState = LOW; 
unsigned long previousMillis = 0; 
const long period = 10000;   // time to turn on
//for app
const String PHONE = "+63959543619";

//*************************************************************************************************//
void setup() {
  //Serial Port begin
  Serial.begin (9600);  
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
  pinMode(Float_Switch, INPUT_PULLUP);
  pinMode(Float_Switch, HIGH);
  //pinMode(Float_Switch2, INPUT_PULLUP);
  pinMode(Float_Switch2, LOW); // JUST FOR TESTING SHOULD REMOVE MMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  
  // Gsm setup Gsm setup  Gsm setup Gsm setup
      Serial.begin(9600); // Serial Communication for Serial Monitor is starting with 9600 of baudrate speed
      mySerial.begin(9600); // Serial Communication for GSM Module is starting with 9600 of baudrate speed
    
      pinMode(device_1, OUTPUT); //Sets the device_1 as an OUTPUT
      pinMode(relayPin, OUTPUT); //Sets the relayPin as an OUTPUT    
      digitalWrite(device_1, LOW); //Sets the device_1 in to OFF state at the beginning
      //digitalWrite(relayPin, LOW); //Sets the relayPin in to OFF state at the beginning      
      // Check if you're currently connected to SIM800L
      while (!mySerial.available()) {
        mySerial.println("AT");
        delay(1000);
        Serial.println("connecting....");
      }    
      Serial.println("Connected..");
    
      mySerial.println("AT+CMGF=1");  //Set SMS Text Mode
      delay(1000);
      mySerial.println("AT+CNMI=1,2,0,0,0");  //procedure, how to receive messages from the network
      delay(1000);
      mySerial.println("AT+CMGL=\"REC UNREAD\""); // Read unread messages
    
      Serial.println("Ready to received Commands..");

      //send message
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+639639874383\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        mySerial.print("The bin is Ready to receive commands... reply BIN ON - to turn on or BIN OFF-to stop | visit http://192.168.1.225/ to monitor the aquabin"); //text content
        updateSerial();
        mySerial.write(26);
      //RTC   RTC  RTC  RTC   RTC  RTC RTC   RTC  RTC RTC   RTC  RTC
      // Set the clock to run-mode, and disable the write protection
      rtc.halt(false);
      rtc.writeProtect(false);
      Serial.begin(9600);
      pinMode(relayPin,OUTPUT);
      digitalWrite(relayPin, LOW);
      Serial.println("Turn off by setup");
      // The following lines can be commented out to use 
      // the values already stored in the DS1302
      rtc.setDOW(FRIDAY);      // Set Day-of-Week to FRIDAY
      rtc.setTime(8, 59, 40);   // Set the time to 12:00:00 (24hr format)
      rtc.setDate(5, 19, 2023); // Set the date to August 6th, 2019 
      //for millis timer
      
}
//********************************************************************//
void loop() {

   // GSM codes receiving//
    if (mySerial.available()) {
    delay(100);

    // Serial buffer
    while (mySerial.available()) {
      incomingByte = mySerial.read();
      incomingData += incomingByte;
    }

    delay(10);
    if (atCommand == false) {
      receivedMessage(incomingData);
    } else {
      atCommand = false;
    }

    //delete messages to save memory
    if (incomingData.indexOf("OK") == -1) {
      mySerial.println("AT+CMGDA=\"DEL ALL\"");
      delay(1000);
      atCommand = true;
    }

    incomingData = "";
  }
  //*******************************************

  if(digitalRead(Float_Switch) == HIGH && digitalRead(Float_Switch2) == LOW){
    Serial.println("Float 1 is on");
      digitalWrite(LED1, HIGH); //Turn LED on

      // RTC RTC  RTC RTC RTC RTC RTC RTC
      t = rtc.getTime();
      Serial.print(t.hour);
      Serial.print(":");
      Serial.print(t.min);
      Serial.print(":");
      Serial.println(t.sec);
      Serial.println("*********");
      if (t.hour == OnHour && t.min == OnMin) {
        if((cm>40) && (cm<60)){
          digitalWrite(relayPin, LOW);
          Serial.println("TURN OFF BY FULL");
        }
        else{
          digitalWrite(relayPin, HIGH);
          Serial.println("AQUABIN ON");
          if(y1 == 1){
            y1 = y1 + 1;
            Serial.print("y ===");
            Serial.println(y1);
            //send message
            mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
            updateSerial();
            mySerial.println("AT+CMGS=\"+639639874383\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
            updateSerial();
            mySerial.print("The bin is Ready Turned on by Timer"); //text content
            updateSerial();
            mySerial.write(26);
          }
          
          
        }        
      }else if (t.hour == OffHour && t.min == OffMin) {
        digitalWrite(relayPin, LOW);
        Serial.println("AQUABIN OFF"); 
        if(y2 == 1){
            y2 = y2 + 1;
            Serial.print("y ===");
            Serial.println(y2);
        //send message
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+639639874383\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        mySerial.print("The bin is Ready Turned off by Timer"); //text content
        updateSerial();
        mySerial.write(26);
        }
      }
     delay (500);
    //####################### Ultrasonic Codes
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
   
    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
  
    cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
    inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
   
    Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    
    delay(500);  
    //##########################
      
      if(cm<=170 && (cm>150)){
        Serial.println("The bin is full");
        digitalWrite(LED2, HIGH);
        //send message
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+639639874383\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        mySerial.print("The bin is full... shutting down... | visit http://192.168.1.225/ to monitor the aquabin"); //text content
        updateSerial();
        mySerial.write(26);
        
        digitalWrite(relayPin, LOW);
        Serial.println("turn off by full");
  
        delay(10000);
        
        
      }
      else if(cm==0){
        
      }
      else if((cm>210) && (cm<230)){
        
        Serial.println("The bin is 70% ");
        digitalWrite(LED2, LOW);
        //send message
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+639639874383\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        mySerial.print("The bin is 70%full...reply BIN OFF-to stop | visit http://192.168.1.225/ to monitor the aquabin"); //text content
        updateSerial();
        mySerial.write(26);
        delay(10000);
        
        
      }
      else if((cm>300)&&(cm<400)){
        
        Serial.println("The bin is EMPTY ");

        //send message
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+639639874383\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        mySerial.print("The bin water is sufficient | The bin is empty...reply BIN ON-to turn on the Aquabin "); //text content
        updateSerial();
        mySerial.write(26);
        delay(5000);
        digitalWrite(LED2, HIGH);
        
      }
    
      
    
  }

 
//  else if(digitalRead(Float_Switch2) == HIGH){
//      Serial.println("Float 2 is on ");
//      Serial.print("Water Overflow");
//        //send message
//        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
//        updateSerial();
//        mySerial.println("AT+CMGS=\"+639639874383\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
//        updateSerial();
//        mySerial.print("The water level is too high... shutting down... | visit http://192.168.1.225/ to monitor the aquabin"); //text content
//        updateSerial();
//        mySerial.write(26);
//        
//        digitalWrite(relayPin, LOW);
//        Serial.println(" turn off by full");
//  
//        delay(10000);
//
//
//  }
 else if(digitalRead(Float_Switch) == LOW && digitalRead(Float_Switch2) == LOW){
    Serial.println("Float 1 is off ");
    //send message
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+639639874383\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        mySerial.print("The bin water level 1 is Insufficient Check bin "); //text content
        updateSerial();
        mySerial.write(26);
        delay(10000);
  }
  

    
   
  
  
}
//***Function 1************************************************************************************/
void receivedMessage(String inputString) {

  //Get The number of the sender
  index = inputString.indexOf('"') + 1;
  inputString = inputString.substring(index);
  index = inputString.indexOf('"');
  number = inputString.substring(0, index);
  Serial.println("Number: " + number);

  //Get The Message of the sender
  index = inputString.indexOf("\n") + 1;
  message = inputString.substring(index);
  message.trim();
  Serial.println("Message: " + message);
  message.toUpperCase(); // uppercase the message received


  //LED TRIAL MODE turn Device 1 ON / 
  if (message.indexOf("D1 ON") > -1) {
    digitalWrite(device_1, HIGH);
    delay(1000);
    Serial.println("Command: Device 1 Turn On.");
  }

  //turn Device 1 OFF
  if (message.indexOf("D1 OFF") > -1) {
    digitalWrite(device_1, LOW);
    Serial.println("Command: Device 1 Turn Off.");
  }

  //turn Device 2 ON
  if (message.indexOf("BIN ON") > -1) {
    
    digitalWrite(relayPin, HIGH);
    delay(1000);
    Serial.println("Command: BIN Turn On.");
    //send message
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+639639874383\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        mySerial.print("Command Received: Bin is ON "); //text content
        updateSerial();
        mySerial.write(26);
        delay(10000);
    
  }

  //turn Device 2 OFF
  if (message.indexOf("BIN OFF") > -1) {
    
    digitalWrite(relayPin, LOW);
    Serial.println("Command: Device 1 Turn Off.");

    //send message
        mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
        updateSerial();
        mySerial.println("AT+CMGS=\"+639639874383\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
        updateSerial();
        mySerial.print("Command Received: Bin is OFF "); //text content
        updateSerial();
        mySerial.write(26);
        delay(10000);
  }

  delay(50);// Added delay between two readings
}
//***********Function 2 **********

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
