int led=2;
int ldr=A0;
int SensorV=0;

void setup() {
  pinMode(led, OUTPUT);// put your setup code here, to run once:
  pinMode(led, INPUT);
  Serial.begin(9600);
}

void loop() {
  SensorV=analogRead(ldr);
  delay(100);
  Serial.println("sensor = ");
  Serial.println(SensorV);
  
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
  // put your main code here, to run repeatedly:

}
