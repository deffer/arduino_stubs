/**
* 1. Stepper motor bipolar
* 2. motor driver L293D
* 3. switch on-off-on to control the motor 
*    on (top) - start routine UP (turn clockwise that many times)
*    off (middle) - stop any ongoing routine
*    on (bottom) - start routine DOWN
* 4. reed switch - to detect the door is at the top (magnet is near the switch)
*    LOW - switch is connected - magnet is near the switch - door at the at the top
* 
* When switch 3 goes up or down (PIN_TOP or PIN_BOTTOP), a routine is started which will move stepper
*   in a direction indicated by switch, which in turn moves the sliding door
*   up or down. When door moves UP, additional check is performed 
*   - if reed switch (4) reads LOW (connected), the door is at the top and we need 
*   to stop the motor.
*/
#include <Stepper.h>

const int stepsPerRevolution = 200;  
const int MAX_STEPS_UP = stepsPerRevolution * 5;
const int MAX_STEPS_DOWN = stepsPerRevolution * 5;

// initialize the stepper library on pins 8 through 11:
// 8 - IN1, 9 - IN2. other side: 10 - IN3, 11 - IN4
// wires of one coil are connected to same side of the driver
Stepper myStepper(stepsPerRevolution, 8,9,10,11);  

// pins
int PIN_TOP = 0;    // input pullup. LOW - door to go up
int PIN_BOTTOM= 2;    // input pullup. LOW - door to go down
int PIN_END_OF_TRACK = 4; // input pullup. LOW - proximity sensor went off
int PIN_ENABLE = 6; // instatly stops or starts the motor

// constants: status of the switch, also routines   
int DEF_UP = 1;
int DEF_OFF = 0;
int DEF_DOWN = 2;

// current and previous states
int prevState = DEF_OFF;

int currentRoutine = DEF_OFF; // reusing DEF_ constants for routine names
int routineStep = 0;

void setup() {  
  // Serial.begin(9600);
  myStepper.setSpeed(30);  // option 2
  
  pinMode(PIN_TOP, INPUT_PULLUP);
  pinMode(PIN_BOTTOM, INPUT_PULLUP);  
  pinMode(PIN_END_OF_TRACK, INPUT_PULLUP);
  pinMode(PIN_ENABLE, OUTPUT); 
  digitalWrite(PIN_ENABLE, LOW); 
}

void loop() {
  // read command (from RF receiver or button) and if it has changed:
  //  compare with current routine:
  //    if different - do something (stop or start)
  //    otherwise continue what we were doing (routine) or not doing
  int currentState = readSwitchStatus();
  
  // if state changed
  if (currentState != prevState){
    prevState = currentState;            
    halt();
    if (currentState == DEF_OFF)
      return;
    else
      routine(currentState, true);
  }else{
    if (currentState != DEF_OFF && currentRoutine != DEF_OFF)
      routine(currentRoutine, false);  
  }    
  
}


void routine(int routineId, bool newCycle){
  int maxSteps = routineId == DEF_UP? MAX_STEPS_UP : MAX_STEPS_DOWN;
  if (currentRoutine != routineId)
    currentRoutine = routineId; 
    
  if (routineId == DEF_UP && digitalRead(PIN_END_OF_TRACK)==LOW){
      halt();    
      return;
  }
  if (newCycle)
    digitalWrite(PIN_ENABLE, HIGH); 
    
  if (routineId == DEF_UP)
    myStepper.step(1); 
  else
    myStepper.step(-1);   
  
  routineStep++;
  if (routineStep >= maxSteps)
    halt();
}

int halt(){
  digitalWrite(PIN_ENABLE, LOW); 
  currentRoutine=DEF_OFF;
  routineStep = 0;
}

int readSwitchStatus(){
  int val = digitalRead(PIN_TOP);
  if (val == LOW){
    return DEF_UP;
  }
  
  val = digitalRead(PIN_BOTTOM);
  if (val == LOW){
    return DEF_DOWN;
  }    
  
  return DEF_OFF;
}
