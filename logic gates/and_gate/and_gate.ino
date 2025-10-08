// C++ code
//
int led = 13;
int b1 =2;
int b2 = 1;

boolean bstate1 = 0;
boolean bstate2 = 0;
boolean ledstate;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
}

void loop()
{
  bstate1 = digitalRead(b1);
  bstate2 = digitalRead(b2);
  ledstate = !(bstate1 ^ bstate2);
  
  digitalWrite(led, ledstate);
}
