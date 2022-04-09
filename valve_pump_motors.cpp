#include "Arduino.h"
#include "valve_pump_motors.h"

 pumps::pumps(){

pinMode(8, INPUT_PULLUP);
pinMode(9, INPUT_PULLUP);
pinMode(10, INPUT_PULLUP);
pinMode(11, INPUT_PULLUP);
pinMode(12, INPUT_PULLUP);
pinMode(13, INPUT_PULLUP);

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

 while ((digitalRead(12) == 1) || (digitalRead(11) == 1)){

    if(digitalRead(12) == 1){
          myservo6.writeMicroseconds(1700);

    }
    
    else{
      myservo6.writeMicroseconds(1500);
    }

    if(digitalRead(10) == 1){
      myservo5.writeMicroseconds(1300);
    }

    else{
      myservo5.writeMicroseconds(1500);
    }
   
  }

  myservo5.writeMicroseconds(1500);
  myservo6.writeMicroseconds(1500);
}
void pumps::waste_blank(){
  
  myservo2.write(0);
  myservo3.write(180);

  while ((digitalRead(13) == 1) || (digitalRead(10) == 1)){

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

  myservo1.write(0);
  myservo2.write(90);

  while ((digitalRead(13) == 1) && (digitalRead(10) == 1)){

    myservo6.writeMicroseconds(1300);
    myservo5.writeMicroseconds(1700);
  }

  myservo6.writeMicroseconds(1500);
  myservo5.writeMicroseconds(1500);
}
