#include "Arduino.h"
#include "valve_pump_motors.h"

 pumps::pumps(){
  light = HIGH;
  up = HIGH;
}

void pumps::pullup_switch(){
 // water sensor




// syringe setup
pinMode(4, INPUT_PULLUP);
pinMode(5, INPUT_PULLUP);
//pinMode(10, INPUT_PULLUP);
//pinMode(11, INPUT_PULLUP);
pinMode(6, INPUT_PULLUP);
pinMode(7, INPUT_PULLUP);

}

void pumps::attach_motors(){

river_valve.attach(8);
test_valve.attach(9);
//blank_valve.attach(10); 

river_water.attach(11);
blank.attach(10);

}

void pumps::get_water(){
  river_valve.write(0);
  test_valve.write(0);
//delay for valve(s)
delay(2000);

 while(digitalRead(5) == LOW){
  river_water.writeMicroseconds(1300);
 }
 river_water.writeMicroseconds(1500);

}

void pumps::test_blank(){
   for(int x=0;x<180;x=x+10){
     test_valve.write(x);
     delay(100);
  }
  blank_valve.write(0);
  //delay for valve(s)
  delay(2000);
   while ((digitalRead(6) == 1)){
     blank.writeMicroseconds(1700);
   }

  blank.writeMicroseconds(1500);
}

void pumps::waste_blank(){
 
  while ((digitalRead(7) == 1)){
          blank.writeMicroseconds(1300);
  }

  blank.writeMicroseconds(1500);
  
}

void pumps::test_water(){

  river_valve.write(180);
  test_valve.write(0);
    //delay for valve(s)
  delay(2000);
  while (digitalRead(4) == 0){
    river_water.writeMicroseconds(1700);
  }

  blank.writeMicroseconds(1500);
}


void pumps::waste_water(){
   for(int x=0;x<180;x=x+10){
     river_valve.write(x);
     delay(100);
  }
  river_valve.write(180);
  test_valve.write(0);
    //delay for valve(s)
  delay(2000);
  while ((digitalRead(5) == 0)){
          river_water.writeMicroseconds(1300);
  }

  river_water.writeMicroseconds(1500);
  
}

void pumps::water_sensor(){

   timeOld = millis();
   timeNow = timeNow;
   water = 0;
   state = 0;
   data = 0;
   serial_output = "W0S0";

   timeNow = millis();
   timePassed = timePassed +(timeNow - timeOld);
   timeOld = timeNow;
   
   if(timePassed > 150){
     data = analogRead(Grove_Water_Sensor);
     data = map(data, 0,1024,0,255);
     if( data>1) {
        water = 1;
     }else {
        water = 0;
     }
     
     Serial.write('W');
     Serial.write(water);
     Serial.write('S');
     Serial.write(state);
     Serial.write('D');
     Serial.write(data);
     Serial.write('\n');
     timePassed = 0;
     state = state+1;
     
     if(state>6){
      state = 0;
     }  
      
}
}
