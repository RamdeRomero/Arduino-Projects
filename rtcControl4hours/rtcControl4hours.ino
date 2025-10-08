// DS1302:  CE pin    -> Arduino Digital 2 -5
//          I/O pin   -> Arduino Digital 3 - 9
//          SCLK pin  -> Arduino Digital 4 - 10
#include <DS1302.h>
int relayPin = 4;
DS1302 rtc(5, 9, 10);
Time t;
byte OnHour   = 12;
byte OnMin    = 1;
byte OffHour  = 12;
byte OffMin   = 2;
byte limit    = 10;

void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  Serial.begin(9600);
  pinMode(relayPin,OUTPUT);
  digitalWrite(relayPin, LOW);
  // The following lines can be commented out to use 
  // the values already stored in the DS1302
  rtc.setDOW(FRIDAY);      // Set Day-of-Week to FRIDAY
  rtc.setTime(12, 0, 0);   // Set the time to 12:00:00 (24hr format)
  rtc.setDate(6, 8, 2019); // Set the date to August 6th, 2019 

  if(digitalRead(relayPin) == HIGH){
    limit = limit +t.sec; 
    Serial.println(limit);
    if(t.sec == limit){
      digitalWrite(relayPin,LOW);
      Serial.println("LIGHT OFF"); 
    }
  }
}

void loop()
{
  t = rtc.getTime();
  Serial.print(t.hour);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(":");
  Serial.println(t.sec);
  Serial.println("*********");
  
//  if (t.hour == OnHour && t.min == OnMin) {
//    digitalWrite(relayPin,HIGH);
//    Serial.println("LIGHT ON");
//  }else if (t.hour == OffHour && t.min == OffMin) {
//    digitalWrite(relayPin,LOW);
//    Serial.println("LIGHT OFF"); 
//  }
  digitalWrite(relayPin,HIGH);
  Serial.println("LIGHT ON");
  
  
 delay (1000);
}
