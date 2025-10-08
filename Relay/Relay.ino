                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      /*Relay module control.
  Serial monitor readings.
  created by the SriTu Tech team.
  Read the code below and use it for any of your creation
*/
void setup() {
  Serial.begin(9600);//enable serial monitor
  pinMode(4, OUTPUT);//define arduino pin D2
}
void loop() {
  digitalWrite(4,HIGH );//relay on
  Serial.println("ON");//print serial monitor ON
  delay(10000);//delay
  digitalWrite(4, LOW);//relay off
  Serial.println("OFF");//print serial monitor OFF
  delay(10000);//delay
}
