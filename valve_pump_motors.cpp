#include "Arduino.h"
#include "valve_pump_motors.h"

 pumps::pumps(){

}

void pumps::pullup_switch(){
  
pinMode(8, INPUT_PULLUP);
pinMode(9, INPUT_PULLUP);
//pinMode(10, INPUT_PULLUP);
//pinMode(11, INPUT_PULLUP);
pinMode(12, INPUT_PULLUP);
pinMode(13, INPUT_PULLUP);

}

void pumps::attach_motors(){

myservo1.attach(2);
myservo2.attach(3);
myservo3.attach(4);

myservo4.attach(5);
myservo6.attach(6);

}

void pumps::get_water(){

myservo2.write(0);
delay(250);
myservo2.write(180);

 myservo4.write(180);

 while(digitalRead(9) == 1){
  myservo4.writeMicroseconds(1300);
 }
 myservo4.writeMicroseconds(1500);

}

void pumps::test_blank(){

  myservo2.write(0);
  myservo3.write(180);


 while ((digitalRead(12) == 1)){
         myservo6.writeMicroseconds(1300);

    }

  myservo6.writeMicroseconds(1500);
}

void pumps::waste_blank(){
  
  myservo2.write(0);
  myservo3.write(180);
  
  while ((digitalRead(13) == 0)){
          myservo6.writeMicroseconds(1300);
  }

  myservo6.writeMicroseconds(1500);
  
}

void pumps::test_water(){
  myservo1.write(0);
  myservo2.write(90);

  while (digitalRead(13) == 0){
     myservo1.write(90);
    delay(150);
    myservo6.writeMicroseconds(1300);
  }

  myservo6.writeMicroseconds(1500);
}


void pumps::waste_water(){
  myservo1.write(0);
  myservo2.write(180);
  
  while ((digitalRead(9) == 0)){
          myservo4.writeMicroseconds(1300);
  }

  myservo4.writeMicroseconds(1500);
  
}
