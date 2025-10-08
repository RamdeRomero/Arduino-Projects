// C++ code
//
int led1 = 13;
int led2 = 12;
int led3 = 11;

int sensor = A0;
void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
   
}

void loop()
{
  unsigned long time = millis();
  int temp = analogRead(sensor);
  //Serial.println(temp);
  Serial.print(time);
  Serial.print("time");
  Serial.println();
  delay(100);
  
  
  if (temp > 151)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    delay(3000);
    digitalWrite(led3, LOW);
    delay(1000);
    digitalWrite(led2, LOW);
    delay(1000);
    digitalWrite(led1, LOW);
    delay(1000);  
  }
  else if (temp < 150)
  {
    // do Thing B
    digitalWrite(led1, HIGH);
    delay(500);
    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led3, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    delay(500);
   
  }
  else if (temp == 151)
  {
    // do Thing B
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    delay(500);
    
  }
  else
  {
    Serial.println("error");
  }

}
