const int BUTTON_PIN = 7;        
const int DEBOUNCE_DELAY = 50;   

int lastSteadyState = LOW;       
int lastFlickerableState = LOW;  
int currentState;                


unsigned long lastDebounceTime = 0; 

void setup() {

  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {

  currentState = digitalRead(BUTTON_PIN);

  if (currentState != lastFlickerableState) {

    lastDebounceTime = millis();

    lastFlickerableState = currentState;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {

    if (lastSteadyState == HIGH && currentState == LOW)
      Serial.println("The button is pressed");
    else if (lastSteadyState == LOW && currentState == HIGH)
      Serial.println("The button is released");
    lastSteadyState = currentState;
  }
}
