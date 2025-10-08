// C++ code

//initialiaze variable for Led and button
int l1 = 3;
int l2 = 5;
int l3 = 6;
int l4 = 9;
int l5 = 10;
int b = 12;
// initialiabe button state
int bstate = 0;

void setup()
{  
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);
  pinMode(l5, OUTPUT);
  pinMode(b, INPUT);
}

void loop()
{
  bstate = digitalRead(b);
  
  if(bstate == HIGH){
    //Parting ways from mid to outer leds 0.5 sec interval
    //mid
    digitalWrite(l3, HIGH);
    delay(500); 
    digitalWrite(l3, LOW);
    delay(500);
    //2nd layer
    digitalWrite(l2, HIGH);
    digitalWrite(l4, HIGH);
    delay(500); 
    digitalWrite(l2, LOW);
    digitalWrite(l4, LOW);
    delay(500); 
    //outer layer
    digitalWrite(l1, HIGH);
    digitalWrite(l5, HIGH);
    delay(500); 
    digitalWrite(l1, LOW);
    digitalWrite(l5, LOW);
    delay(500);
    //repeat parting ways
        digitalWrite(l3, HIGH);
    delay(500); 
    digitalWrite(l3, LOW);
    delay(500);
    //2nd layer
    digitalWrite(l2, HIGH);
    digitalWrite(l4, HIGH);
    delay(500); 
    digitalWrite(l2, LOW);
    digitalWrite(l4, LOW);
    delay(500); 
    //outer layer
    digitalWrite(l1, HIGH);
    digitalWrite(l5, HIGH);
    delay(500); 
    digitalWrite(l1, LOW);
    digitalWrite(l5, LOW);
    delay(500);

  }
  else{
    digitalWrite(l1, HIGH);
    delay(1000); 
    digitalWrite(l1, LOW);
    delay(1000); 
    //4
    digitalWrite(l2, HIGH);
    delay(1000); 
    digitalWrite(l2, LOW);
    delay(1000); 
    //3
    digitalWrite(l3, HIGH);
    delay(1000); 
    digitalWrite(l3, LOW);
    delay(1000); 
    //2
    digitalWrite(l4, HIGH);
    delay(1000); 
    digitalWrite(l4, LOW);
    delay(1000); 
    //1
    digitalWrite(l5, HIGH);
    delay(1000); 
    digitalWrite(l5, LOW);
    delay(1000);
  }
}
