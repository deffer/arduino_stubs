/**
* 1. Stepper motor bipolar
* 2. motor driver L293D
* 3. button momentary - connects power (5V) to the EN1 and EN2 driver legs
* 4. switch on-off to change motor direction, e.g.
*    off (HIGH) - clockwise, door moves up 
*    on (LOW) - counterclockwise, door moves down
* 5. reed switch - to detect the door is at the top (magnet is near the switch)
*    LOW - switch is connected - magnet is near the switch - door at the at the top
* 
* When button number 3 is pressed it enabled power to the driver, which is moving stepper
*   in the direction indicated by switch 4, which in turn moves the sliding door
*   up or down. If switch is off (HIGH, door moves up), additional check is performed 
*   - if reed switch reads LOW (connected), the door is at the top and we need 
*   to stop the motor.
*/
#include <Stepper.h>

const int stepsPerRevolution = 200;  

// initialize the stepper library on pins 8 through 11:
// 8 - IN1, 9 - IN2. other side: 10 - IN3, 11 - IN4
// wires of one coil are connected to same side of the driver
Stepper myStepper(stepsPerRevolution, 8,9,10,11);  

int PIN_DIRECTION = 0;    // input pullup. LOW - door goes down
int PIN_END_OF_TRACK = 3; // input pullup. LOW - proximity sensor went off
   

void setup() {  
  // Serial.begin(9600);
  myStepper.setSpeed(30);  // option 2
  
  pinMode(PIN_DIRECTION, INPUT_PULLUP);
  pinMode(PIN_END_OF_TRACK, INPUT_PULLUP);
}

void loop() {
  // get the sensor value
  int val = digitalRead(PIN_DIRECTION);
  if (val == HIGH){
    if (digitalRead(PIN_END_OF_TRACK) == HIGH)
      myStepper.step(1);
  } else
    myStepper.step(-1);  

}

