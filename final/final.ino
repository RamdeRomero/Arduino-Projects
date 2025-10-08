//DEFINE TTGO TCALL PINS
#define MODEM_RST            2
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26
#define I2C_SDA              21
#define I2C_SCL              22
//BLYNK SET UP
#define BLYNK_PRINT Serial
#define BLYNK_HEARTBEAT 30
//SMS TARGET
#define TINY_GSM_MODEM_SIM800 
#define SMS_TARGET  "+639663744570"

//LIBRARIES
#include <TinyGPS++.h> //https://github.com/mikalhart/TinyGPSPlus
#include <AceButton.h> // https://github.com/bxparks/AceButton
#include <TinyGsmClient.h> // https://github.com/vshymanskyy/TinyGSM
#include <BlynkSimpleTinyGSM.h> //https://github.com/blynkkk/blynk-library
#include <Wire.h>
#include "utilities.h"
#include <EEPROM.h> 
//ESP NOW CONNECTION
#include <esp_now.h>
#include <WiFi.h>
esp_now_peer_info_t slave;
#define CHANNEL 0
#define PRINTSCANRESULTS 0
#define DELETEBEFOREPAIR 0
using namespace ace_button;

//Buttons
#define SMS_Button 32

// Emergency Number and Message
String message = "It's an Emergency! Please check Blynk Application or visit\n";
String mobile_number = "+639663744570";
String message_with_data;

// Variables for storing GPS Data
float latitude;
float longitude;
float speed;
float satellites;
String direction;
boolean DEBUG_MODE = 1;
//TEXT BATTERY
const int Analog_channel_pin= 15;
float ADC_VALUE = 0;
float voltage_value = 0;
bool smsSent = false;
//ULTRASONIC
const int trigPin = 5;
const int echoPin = 18;
const int buzzer = 19;
long duration;
int distance;
const int totalPhoneNo = 5;
String phoneNo[totalPhoneNo] = {"","","","",""};
int offsetPhone[totalPhoneNo] = {0,13,26,39,52};
String tempPhone = "";

String smsStatus;
String senderNumber;
String receivedDate;
String msg;
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int safetyDistance;
} struct_message;

// Create a struct_message called myData
struct_message distance1;

ButtonConfig config2;
AceButton sms_button(&config2);

void handleEvent_sms(AceButton*, uint8_t, uint8_t);

// Set serial for GPS Module
#define SerialMon Serial

// Hardware Serial for builtin GSM Module
#define SerialAT Serial1

const char apn[]  = "internet.globe.com.ph";
const char user[] = "";
const char pass[] = "";

//Auth Token in the Blynk App.
const char auth[] = "JQzuIF2zU8pL2eVOs5JcGxzfKI0TrXv3";

//static const int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 9600 ;

TinyGPSPlus gps;
WidgetMap myMap(V0);
//SoftwareSerial ss(RXPin, TXPin);
BlynkTimer timer;
TinyGsm modem(SerialAT);
unsigned int move_index = 1;

void checkGPS()
{
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check connections again."));
    Blynk.virtualWrite(V4, "GPS ERROR");
  }
}

void loop()
{
  
  while (Serial.available() > 0)
  {
    if (gps.encode(Serial.read()))
      displayInfo(SerialAT.readString());
      sms_button.check(); 
  }

  timer.run();
 
}

void displayInfo(String buff)
{
  String phoneNumber;
  Serial.println(buff);     
  unsigned int len, index;
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  //Remove sent "AT Command" from the response string.
  index = buff.indexOf("\r");
  buff.remove(0, index+2);
  buff.trim();
  

 if(buff != "OK"){
    index = buff.indexOf(":");
    String cmd = buff.substring(0, index);
    cmd.trim();
    
    buff.remove(0, index+2);
  
    if(cmd == "+CMTI"){
      //get newly arrived memory location and store it in temp
      index = buff.indexOf(",");
      String temp = buff.substring(index+1, buff.length()); 
      temp = "AT+CMGR=" + temp + "\r"; 
      //get the message stored at memory location "temp"
      SerialAT.println(temp); 
    }
   
    else if(cmd == "+CMGR"){
      extractSms(buff);
 
      if(msg.equals("r") && phoneNo[0].length() != 13) {
        writeToEEPROM(offsetPhone[0],senderNumber);
        phoneNo[0] = senderNumber;
        String text = "Number is Registered: ";
        text = text + senderNumber;
        debugPrint(text);
        modem.sendSMS("Number is Registered", senderNumber);
      }
 
      if(comparePhone(senderNumber)){
         if(msg == "r2="){  
      //mmmmmmm
      Serial.println(offsetPhone[1]);
      writeToEEPROM(offsetPhone[1],tempPhone);
      phoneNo[1] = tempPhone;
      String text = "Phone2 is Registered: ";
      text = text + tempPhone;
      debugPrint(text);
      modem.sendSMS(mobile_number,text);
  }
 
  else if(msg == "r3="){  
      writeToEEPROM(offsetPhone[2],tempPhone);
      phoneNo[2] = tempPhone;
      String text = "Phone3 is Registered: ";
      text = text + tempPhone;
      modem.sendSMS(mobile_number,text);
  }
  
  else if(msg == "r4="){  
      writeToEEPROM(offsetPhone[3],tempPhone);
      phoneNo[3] = tempPhone;
      String text = "Phone4 is Registered: ";
      text = text + tempPhone;
      modem.sendSMS(mobile_number,text);
  }
  
  else if(msg == "r5="){  
      writeToEEPROM(offsetPhone[4],tempPhone);
      phoneNo[4] = tempPhone;
      String text = "Phone5 is Registered: ";
      text = text + tempPhone;
      modem.sendSMS(mobile_number,text);
  }
 
  else if(msg == "list"){  
      String text = "";
      if(phoneNo[0])
        text = text + phoneNo[0]+"\r\n";
      if(phoneNo[1])
        text = text + phoneNo[1]+"\r\n";
      if(phoneNo[2])
        text = text + phoneNo[2]+"\r\n";
      if(phoneNo[3])
        text = text + phoneNo[3]+"\r\n";
      if(phoneNo[4])
        text = text + phoneNo[4]+"\r\n";
        
      debugPrint("List of Registered Phone Numbers: \r\n"+text);
      modem.sendSMS(mobile_number,text );
  }
 
  else if(msg == "del=1"){  
      writeToEEPROM(offsetPhone[0],"");
      phoneNo[0] = "";
      modem.sendSMS(mobile_number,"Phone1 is deleted." );
  }
 
  else if(msg == "del=2"){  
      writeToEEPROM(offsetPhone[1],"");
      phoneNo[1] = "";
      debugPrint("Phone2 is deleted.");
      modem.sendSMS(mobile_number,"Phone2 is deleted." );
  }
  
  else if(msg == "del=3"){  
      writeToEEPROM(offsetPhone[2],"");
      phoneNo[2] = "";
      debugPrint("Phone3 is deleted.");
      modem.sendSMS(mobile_number,"Phone3 is deleted." );
  }
  
  else if(msg == "del=4"){  
      writeToEEPROM(offsetPhone[3],"");
      phoneNo[3] = "";
      debugPrint("Phone4 is deleted.");
      modem.sendSMS( mobile_number,"Phone4 is deleted.");
  }
  
  else if(msg == "del=5"){  
      writeToEEPROM(offsetPhone[4],"");
      phoneNo[4] = "";
      debugPrint("Phone5 is deleted.");
      modem.sendSMS(mobile_number,"Phone5 is deleted." );
  }
  
  if(msg == "del=all"){  
      writeToEEPROM(offsetPhone[0],"");
      writeToEEPROM(offsetPhone[1],"");
      writeToEEPROM(offsetPhone[2],"");
      writeToEEPROM(offsetPhone[3],"");
      writeToEEPROM(offsetPhone[4],"");
      phoneNo[0] = "";
      phoneNo[1] = "";
      phoneNo[2] = "";
      phoneNo[3] = "";
      phoneNo[4] = "";
      offsetPhone[0] = NULL;
      offsetPhone[1] = NULL;
      offsetPhone[2] = NULL;
      offsetPhone[3] = NULL;
      offsetPhone[4] = NULL;
      debugPrint("All phone numbers are deleted.");
      modem.sendSMS( mobile_number, "All phone numbers are deleted.");
  }
 
  smsStatus = "";
  senderNumber="";
  receivedDate="";
  msg="";
  tempPhone = "";
        //sendLocation();
      }
      //-------------------------------------------------------
    }
    
  }
  else{
  //The result of AT Command is "OK"
  }
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600  );
  WiFi.mode(WIFI_STA);
  Serial.print("STA MAC: "); Serial.println(WiFi.macAddress());
  InitESPNow();
  esp_now_register_send_cb(OnDataSent);

  Wire.begin(I2C_SDA, I2C_SCL);
  bool isOk = setPowerBoostKeepOn(1);
  SerialMon.println(String("IP5306 KeepOn ") + (isOk ? "OK" : "FAIL"));

  // Set-up modem reset, enable, power pins
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);

  //SMS BUTTON AS INPUT
  pinMode(SMS_Button, INPUT);

  //TTGO TCALL 
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);

  // Set GSM module baud rate and UART pins
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem: ");
  SerialMon.println(modemInfo);
  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork(240000L)) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" OK");

  if (modem.isNetworkConnected()) {
    SerialMon.println("Network connected");
  }

  SerialMon.print(F("Connecting to APN: "));
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, user, pass)) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" OK");
  //  ss.begin(GPSBaud);
  Blynk.begin(auth, modem, apn, user, pass);
  timer.setInterval(5000L, checkGPS);
 delay(1000);
  EEPROM.begin(512);
  Serial.println("List of Registered Phone Numbers");
  for (int i = 0; i < totalPhoneNo; i++){
    phoneNo[i] = readFromEEPROM(offsetPhone[i]);
    if(phoneNo[i].length() != 13)
      {phoneNo[i] = "";Serial.println(String(i+1)+": empty");}
    else
      {Serial.println(String(i+1)+": "+phoneNo[i]);}
  }
  smsStatus = "";
  senderNumber="";
  receivedDate="";
  msg="";
  delay(9000);
  SerialAT.println("AT+CMGF=1"); //SMS text mode
  SerialAT.println("AT+CMGD=1,4");
  delay(1000);
  config2.setEventHandler(handleEvent_sms);
  sms_button.init(SMS_Button);
      digitalWrite(buzzer, HIGH);
  delay (500);
  digitalWrite(buzzer, LOW);
  delay (100);
    digitalWrite(buzzer, HIGH);
  delay (500);
  digitalWrite(buzzer, LOW);
  delay (100);
}

//REGISTER PHONE NUMBER CODE AREA//
String readFromEEPROM(int addrOffset)
{
  int len = 13;
  char data[len + 1];
  for (int i = 0; i < len; i++)
  {
    data[i] = EEPROM.read(addrOffset + i);
  }
  data[len] = '\0';
  return String(data);
}

void writeToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = 13; //strToWrite.length();
  //EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    //meee
    //Serial.print(addrOffset + i);
    //Serial.println(strToWrite[addrOffset + i]);
    EEPROM.write(addrOffset + i, strToWrite[i]);
  }

  // actually write the content of byte-array cache to
  // hardware flash.  flash write occurs if and only if one or more byte
  // in byte-array cache has been changed, but if so, ALL 512 bytes are 
  // written to flash
  EEPROM.commit();

}
boolean comparePhone(String number)
{
  boolean flag = 0;
  //--------------------------------------------------
  for (int i = 0; i < totalPhoneNo; i++){
    phoneNo[i] = readFromEEPROM(offsetPhone[i]);
    if(phoneNo[i].equals(number)){
      //Serial.println(phoneNo[i]);
      flag = 1;
      break;
    }
  }
  //--------------------------------------------------
  return flag;
}
boolean compareWithoutCountryCode(String number)
{
  boolean flag = 0;
  //--------------------------------------------------
  for (int i = 0; i < totalPhoneNo; i++){
    phoneNo[i] = readFromEEPROM(offsetPhone[i]);
    //remove first 3 digits (country code)
    phoneNo[i].remove(0,3);
    //Serial.println("meee1: "+phoneNo[i]);
    if(phoneNo[i].equals(number)){
      //Serial.println(phoneNo[i]);
      flag = 1;
      break;
    }
  }
  //--------------------------------------------------
  return flag;
}

void parseData(String buff){
  Blynk.run();
  Serial.println(buff);     
  unsigned int len, index;
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  //Remove sent "AT Command" from the response string.
  index = buff.indexOf("\r");
  buff.remove(0, index+2);
  buff.trim();
  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

  if(buff != "OK"){
    
    index = buff.indexOf(":");
    String cmd = buff.substring(0, index);
    cmd.trim();
    
    buff.remove(0, index+2);

    if(cmd == "+CMTI"){
      //get newly arrived memory location and store it in temp
      index = buff.indexOf(",");
      String temp = buff.substring(index+1, buff.length()); 
      temp = "AT+CMGR=" + temp + "\r"; 
      //get the message stored at memory location "temp"
      SerialAT.println(temp); 
    }
    else if(cmd == "+CMGR"){
      extractSms(buff);
      //-------------------------------------------------------
      if(msg.equals("r") && phoneNo[0].length() != 13) {
        writeToEEPROM(offsetPhone[0],senderNumber);
        phoneNo[0] = senderNumber;
        String text = "Number is Registered: ";
        text = text + senderNumber;
        debugPrint(text);
        modem.sendSMS("Number is Registered", senderNumber);
      }
      //-------------------------------------------------------
      if(comparePhone(senderNumber)){
        doAction(senderNumber);
        //sendLocation();
      }
      //-------------------------------------------------------
    }
    //NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN
  }
  else{
  //The result of AT Command is "OK"
  }
     
  
}
void doAction(String phoneNumber){
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  if(msg == "r2="){  
      Blynk.disconnect();
      Serial.println(offsetPhone[1]);
      writeToEEPROM(offsetPhone[1],tempPhone);
      phoneNo[1] = tempPhone;
      String text = "Phone2 is Registered: ";
      text = text + tempPhone;
      debugPrint(text);
      modem.sendSMS(mobile_number,text);
      Blynk.connect();
      
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  else if(msg == "r3="){  
    Blynk.disconnect();
      writeToEEPROM(offsetPhone[2],tempPhone);
      phoneNo[2] = tempPhone;
      String text = "Phone3 is Registered: ";
      text = text + tempPhone;
      modem.sendSMS(mobile_number,text);
      Blynk.connect();
       
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  else if(msg == "r4="){  
    Blynk.disconnect();
   
      writeToEEPROM(offsetPhone[3],tempPhone);
      phoneNo[3] = tempPhone;
      String text = "Phone4 is Registered: ";
      text = text + tempPhone;
      modem.sendSMS(mobile_number,text);
      Blynk.connect();
      
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  else if(msg == "r5="){  
    Blynk.disconnect();
      writeToEEPROM(offsetPhone[4],tempPhone);
      phoneNo[4] = tempPhone;
      String text = "Phone5 is Registered: ";
      text = text + tempPhone;
      modem.sendSMS(mobile_number,text);
      Blynk.connect();
      
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  else if(msg == "list"){  
    Blynk.disconnect();
      String text = "";
      if(phoneNo[0])
        text = text + phoneNo[0]+"\r\n";
      if(phoneNo[1])
        text = text + phoneNo[1]+"\r\n";
      if(phoneNo[2])
        text = text + phoneNo[2]+"\r\n";
      if(phoneNo[3])
        text = text + phoneNo[3]+"\r\n";
      if(phoneNo[4])
        text = text + phoneNo[4]+"\r\n";
        
      debugPrint("List of Registered Phone Numbers: \r\n"+text);
      modem.sendSMS(mobile_number,text );
      Blynk.connect();
       
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  else if(msg == "del=1"){  
    Blynk.disconnect();
      writeToEEPROM(offsetPhone[0],"");
      phoneNo[0] = "";
      modem.sendSMS(mobile_number,"Phone1 is deleted." );
      Blynk.connect();
       
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  else if(msg == "del=2"){ 
    Blynk.disconnect(); 
      writeToEEPROM(offsetPhone[1],"");
      phoneNo[1] = "";
      debugPrint("Phone2 is deleted.");
      modem.sendSMS(mobile_number,"Phone2 is deleted." );
      Blynk.connect();
      
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  else if(msg == "del=3"){  
    Blynk.disconnect();
      writeToEEPROM(offsetPhone[2],"");
      phoneNo[2] = "";
      debugPrint("Phone3 is deleted.");
      modem.sendSMS(mobile_number,"Phone3 is deleted." );
      Blynk.connect();
       
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  else if(msg == "del=4"){
    Blynk.disconnect();  
      writeToEEPROM(offsetPhone[3],"");
      phoneNo[3] = "";
      debugPrint("Phone4 is deleted.");
      modem.sendSMS( mobile_number,"Phone4 is deleted.");
      Blynk.connect();
       
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  else if(msg == "del=5"){  
    Blynk.disconnect();
      writeToEEPROM(offsetPhone[4],"");
      phoneNo[4] = "";
      debugPrint("Phone5 is deleted.");
      modem.sendSMS(mobile_number,"Phone5 is deleted." );
      Blynk.connect();
      
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM  
  if(msg == "del=all"){  
    Blynk.disconnect();
      writeToEEPROM(offsetPhone[0],"");
      writeToEEPROM(offsetPhone[1],"");
      writeToEEPROM(offsetPhone[2],"");
      writeToEEPROM(offsetPhone[3],"");
      writeToEEPROM(offsetPhone[4],"");
      phoneNo[0] = "";
      phoneNo[1] = "";
      phoneNo[2] = "";
      phoneNo[3] = "";
      phoneNo[4] = "";
      offsetPhone[0] = NULL;
      offsetPhone[1] = NULL;
      offsetPhone[2] = NULL;
      offsetPhone[3] = NULL;
      offsetPhone[4] = NULL;
      debugPrint("All phone numbers are deleted.");
      modem.sendSMS( mobile_number, "All phone numbers are deleted.");
      Blynk.connect();
  }
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  smsStatus = "";
  senderNumber="";
  receivedDate="";
  msg="";
  tempPhone = "";
 
}
void debugPrint(String text){
  if(DEBUG_MODE == 1)
    Serial.println(text);
}
void extractSms(String buff){
   unsigned int index;
   
    index = buff.indexOf(",");
    smsStatus = buff.substring(1, index-1); 
    buff.remove(0, index+2);
    
    senderNumber = buff.substring(0, 13);
    buff.remove(0,19);
   
    receivedDate = buff.substring(0, 20);
    buff.remove(0,buff.indexOf("\r"));
    buff.trim();
    
    index =buff.indexOf("\n\r");
    buff = buff.substring(0, index);
    buff.trim();
    msg = buff;
    buff = "";
    msg.toLowerCase();

    String tempcmd = msg.substring(0, 3);
    if(tempcmd.equals("r1=") || tempcmd.equals("r2=") ||
       tempcmd.equals("r3=") || tempcmd.equals("r4=") ||
       tempcmd.equals("r5=")){
        
        tempPhone = msg.substring(3, 16);
        msg = tempcmd;
        //debugPrint(msg);
        //debugPrint(tempPhone);
    }     
}
