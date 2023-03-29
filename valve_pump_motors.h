#ifndef lib
#define lib
#include <Servo.h>
#include "Arduino.h"
#define Grove_Water_Sensor A0 // Attach Water sensor to Arduino Digital Pin 8
#define LED 13 // Attach an LED to Digital Pin 9 (or use onboard LED)


class pumps {
   public:

  pumps();
   int x;
   int y; 
   bool light;
   unsigned long timeNow,timeOld,timePassed;
   uint8_t water,state;
   int data;
   String serial_output;  
   bool up;


   
//valve controls
Servo river_valve;
Servo test_valve;
Servo blank_valve;

//syringe motors
Servo river_water;
//Servo myservo5;
Servo blank;

void water_sensor();
void get_water();
void test_blank();
void waste_blank();
void test_water();
void waste_water();
void attach_motors();
void pullup_switch();

bool recieve_testing_mode();

};
#endif
