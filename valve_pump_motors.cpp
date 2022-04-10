#include "Arduino.h"
#include "valve_pump_motors.h"

 pumps::pumps(){

}

void pumps::pullup_switch(){
  
pinMode(8, INPUT_PULLUP);
pinMode(9, INPUT_PULLUP);
pinMode(10, INPUT_PULLUP);
pinMode(11, INPUT_PULLUP);
pinMode(12, INPUT_PULLUP);
pinMode(13, INPUT_PULLUP);

}

void pumps::attach_motors(){

myservo1.attach(2);
myservo2.attach(3);
myservo3.attach(4);

myservo4.attach(5);
myservo5.attach(6);
myservo6.attach(7);

}

void pumps::get_water(){

 myservo4.write(180);

 while(digitalRead(9) == 1){
  myservo4.writeMicroseconds(1300);
 }
 myservo4.writeMicroseconds(1500);
}

void pumps::test_blank(){

  myservo2.write(0);
  myservo3.write(180);
  Serial.println("I'm in test blank");


 while ((digitalRead(12) == 1) || (digitalRead(11) == 1)){
      Serial.println(digitalRead(12));
      Serial.println(digitalRead(11));

    if(digitalRead(12) == 1){
          myservo6.writeMicroseconds(1300);
          Serial.println("Im in the if statement");
          Serial.println(digitalRead(12));

    }
    
    else{
      myservo6.writeMicroseconds(1500);
      Serial.println("im in else statement");
      break;
    }

    if(digitalRead(10) == 1){
      myservo5.writeMicroseconds(1700);
    }

    else{
      myservo5.writeMicroseconds(1500);
    }
    Serial.println("I'm in the first loop");
  }

  myservo5.writeMicroseconds(1500);
  myservo6.writeMicroseconds(1500);
}

void pumps::waste_blank(){
  
  myservo2.write(0);
  myservo3.write(180);
  
  while ((digitalRead(13) == 0) || (digitalRead(10) == 1)){

    if( digitalRead(13) == 1){
          myservo6.writeMicroseconds(1300);

    }
    
    else{
      myservo6.writeMicroseconds(1500);
    }

    if(digitalRead(10) == 1){
      myservo5.writeMicroseconds(1700);
    }

    else{
      myservo5.writeMicroseconds(1500);
    }
   
  }

  myservo5.writeMicroseconds(1500);
  myservo6.writeMicroseconds(1500);
  
}

void pumps::test_water(){
  delay(150);
  //write(0)
  myservo1.write(0);
  myservo2.write(90);
  Serial.println("I'm in test water");
// (digitalRead(13) == 0) && (digitalRead(10) == 0)
  while (1){
     myservo1.write(90);
    delay(150);
    myservo6.writeMicroseconds(1300);
    myservo5.writeMicroseconds(1700);

    Serial.println("I'm in the second loop");
  }

  myservo6.writeMicroseconds(1500);
  myservo5.writeMicroseconds(1500);
}

bool recieve_boat_mode(int val){
  return true;
}

void testing_mode(){
   
}
