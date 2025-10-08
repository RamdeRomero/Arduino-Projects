// C++ code
//
int led = 11;
int pot = A0;

int potVal = 0;
int output = 0;


void setup()
{
  pinMode(led, OUTPUT);
  pinMode(pot, INPUT);
  Serial.begin(9600);
}

void loop()
{
  potVal = analogRead(pot);
  //Serial.println(potVal);
  output = map(potVal, 0, 1023, 0, 255);
  analogWrite(led, output);
  
  Serial.print("pot= ");
  Serial.print(potVal);
  Serial.print("\t output = ");
  Serial.println(output);

  
}
