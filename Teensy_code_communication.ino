// This is the Teensy UART code

IntervalTimer timer;
String data = "hi";
void setup() {
  // Begin the Serial at 9600 Baud
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

void loop() {
  if(Serial1.available()){
    data = Serial1.readString();
    delay(500);
  }

   //Serial.println(data);
   Serial.println(data.substring(0,3));
   
  if(data.substring(0,5) == "Start"){
    digitalWrite(13, LOW);
    int value;
    //incrementing analog read to increment voltage
    for(int i; (0 <= i) && (i < 1021); i++){
      //try to implement timer i
      analogWrite(A14, i);
      value = analogRead(A14);
      //Serial.println(value);
      float voltage = value * (2.0 / 1021.0)-1;
      Serial.println(voltage);
      delay(250);
    }
    Serial1.println("Done");
    data = "Done";
  }
  while(data.substring(0,5) != "Start"){
    digitalWrite(13,HIGH);
  }
}
