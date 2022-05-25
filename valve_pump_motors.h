#ifndef lib
#define lib
#include <Servo.h>
#include "Arduino.h"



class pumps {
   public:

  pumps();
   int x;
   int y; 
   
//valve controls
Servo myservo1;
Servo myservo2;
Servo myservo3;

//syringe motors
Servo myservo4;
//Servo myservo5;
Servo myservo6;

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
