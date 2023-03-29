
#include <Servo.h>
#include "valve_pump_motors.h"


pumps p;
Servo myservo;

void setup() {
Serial.begin(115200);
//p.myservo1.attach(2);
p.attach_motors();
p.pullup_switch();

}



void loop() {
  //checks to see if the pixhawk has written anything to the arduino
  if(Serial.available() > 0){
    //checks to see if pixhawk is telling the arduino to start PFAS testing
   if(Serial.read() == '1'){
      p.get_water();
      p.test_blank();
      initiate_potentiostat();
      p.waste_blank();
      p.test_water();
      initiate_potentiostat();
      p.waste_water();
   }
  }
}

void initiate_potentiostat(){
  //tells the teensy 3.2 to start the potentiostat
  //Serial.println("Start");
  delay(15000);
 
}
