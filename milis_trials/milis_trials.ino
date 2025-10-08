void setup() {
   // put your setup code here, to run once:
   Serial.begin(9600);
   long int t1 = millis();
   //task_whose_time_is_to_be_measured();
   long int t2 = millis();
   Serial.print("Time taken by the task: "); Serial.print(t2-t1); Serial.println(" milliseconds");
}
void loop() {
   // put your main code here, to run repeatedly:
}
