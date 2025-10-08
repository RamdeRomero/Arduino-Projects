
int led1 = 3;

void setup()
{
  pinMode(led1, OUTPUT);
}

void loop()
{
  
  digitalWrite(led1, HIGH);
  delay(1000);
  digitalWrite(led1, LOW);
  delay(1000);
}
