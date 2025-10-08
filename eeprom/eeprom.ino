#include <EEPROM.h>

int brightness;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EEPROM.write(0, 25);

}

void loop() {
  // put your main code here, to run repeatedly:
  brightness = EEPROM.read(0);
  Serial.println(brightness);
  delay(500);

}
