
int relayPin = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  //digitalWrite(relayPin, HIGH);
  
//  delay(500);
//  Serial.println( millis() );
}

void loop() {
  // put your main code here, to run repeatedly:
  method2();

}

void method2() {
  long startTime = millis();
  long duration = 3000;
  long endtime = startTime + duration;
  
  Serial.print("Start Time = " + String(startTime) );
  Serial.println(" duration = " + String(duration) );
  Serial.println(" endtime = " + String(endtime) );
  if(digitalRead(relayPin) == HIGH){
    while(millis()<startTime + duration){
    digitalWrite(relayPin, LOW);
    
    }
    digitalWrite(relayPin, HIGH);
  
    while(true);
  }
  delay(1000);
  
  
}
