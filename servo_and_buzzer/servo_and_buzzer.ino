// C++ code
//

#include <Servo.h>

int sensorVal = 0;
int motorVal = 0;

int led = 13;
int sen = A0;
int buz = 12;

Servo servo_9;

void setup()
{
  pinMode(sen, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buz, OUTPUT);
  servo_9.attach(9);
  Serial.begin (9600); 
}

void loop()
{
  sensorVal = analogRead(sen);
  motorVal = map(sensorVal, 0, 1023, 0, 180);
  if(sensorVal > 500){
    digitalWrite(led, HIGH); 
    tone(buz,1000);  
  }
  else if(sensorVal < 500){
    digitalWrite(led, LOW);
    noTone(buz);
  }  
  servo_9.write(motorVal);
  delay(100);  
  Serial.print("pot= ");
  Serial.print(sensorVal);
  Serial.print("\t angle = ");
  Serial.println(motorVal);  
}
