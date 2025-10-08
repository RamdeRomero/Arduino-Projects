// C++ code
//
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

int led = 4;
int Buzzer= 2;
//PIR
int PIR= 3;
int PIRval= 0;
//Photoresistor
int bright;
int Lsensor = A0;
//LCD 
const int rows = 2;
const int cols = 16;
const int rs = 12, e = 13, d4=11,d5=10,d6=9,d7=8;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
LiquidCrystal lcd(12, 13, 11, 10, 9, 8);

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(Lsensor, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(PIR, INPUT);
  Serial.begin(9600);
  lcd.begin(cols, rows);
   
}

void loop()
{

  bright = analogRead(Lsensor); 
  Serial.print("bright = ");
  Serial.print(bright);
  Serial.print("\t brightness = ");
  Serial.println(bright); 
  //for light sensor
  
  lcd.setCursor(0, 0); // col, line
  lcd.setCursor(0, 0); 
    lcd.write("Motion Sensor");
  
  if(bright > 150){
  //day
    lcd.setCursor(0, 0); 
    lcd.write("Motion Sensor");
 
    
  }
  else if(bright < 150){
    //night
    PIRval = digitalRead(PIR);
    if(PIRval == HIGH){
      digitalWrite(led, HIGH);
      digitalWrite(Buzzer, HIGH);
      //Serial.println("Movement Detected");
    }
    else {
      digitalWrite(led, LOW);
      digitalWrite(Buzzer, LOW);
      //Serial.println("No Movement Detected");
    }
  }
}
