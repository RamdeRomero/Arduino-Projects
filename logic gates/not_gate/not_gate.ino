// C++ code
//
int led = 13;
int b1 =2;

boolean bstate1 = 0;
boolean ledstate;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(b1, INPUT);
}

void loop()
{
  bstate1 = digitalRead(b1);
  ledstate = !bstate1;
  
  digitalWrite(led, ledstate);
}
