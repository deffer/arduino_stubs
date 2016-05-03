
/* 
 Stepper Motor Control - one step at a time
 
 This program drives a unipolar or bipolar stepper motor. 
 The motor is attached to digital pins 8 - 11 of the Arduino.
 
 The motor will step one step at a time, very slowly.  You can use this to
 test that you've got the four wires of your stepper wired to the correct
 pins. If wired correctly, all steps should be in the same direction.
 
 Use this also to count the number of steps per revolution of your motor,
 if you don't know it.  Then plug that number into the oneRevolution
 example to see if you got it right.
 
 Created 30 Nov. 2009
 by Tom Igoe
 
 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
                                     // for your motor

// initialize the stepper library on pins 8 through 11:
// 8 - IN1, 9 - IN2. other side: 10 - IN3, 11 - IN4
// wires of each coil are connected to one side of driver
Stepper myStepper(stepsPerRevolution, 8,9,10,11);            

int stepCount = 0;         // number of steps the motor has taken
int previous = 0;        // option 2

void setup() {
  // initialize the serial port:
  // Serial.begin(9600);
  myStepper.setSpeed(30);  // option 2
}

void loop() {
  // get the sensor value
  int val = analogRead(0);

  // move a number of steps equal to the change in the
  // sensor reading
  if (val-previous !=0 )
    myStepper.step(val - previous);

  // remember the previous value of the sensor
  previous = val;
  
  // step one step:
  //myStepper.step(1);
  //Serial.print("steps:" );
  //Serial.println(stepCount);
  //stepCount++;
  //delay(500);
}

