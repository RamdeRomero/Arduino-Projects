int LED = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  Serial.println("On");
  delay(1000);
  digitalWrite(LED, LOW);
  Serial.println("OFF");
  delay(1000);
  

}
