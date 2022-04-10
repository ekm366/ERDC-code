
#include <Servo.h>
#include "valve_pump_motors.h"

pumps p;

void setup() {
Serial.begin(9600);
//p.myservo1.attach(2);
p.attach_motors();
p.pullup_switch();

}



void loop() {
p.attach_motors();
p.pullup_switch();
p.test_blank();


}
