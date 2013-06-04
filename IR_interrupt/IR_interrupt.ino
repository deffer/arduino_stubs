/*A simple interrupt base class to read IR input from the TSOP382 receiver diode -The user can poll “ir.available()” in their loop to see if a new key has been pressed, leaving the Arduino available for other processing

Jordan Erenrich jordan.erenrich AT gmail.com Oct 4, 2012 */

define START_BIT 2200 //Start bit threshold (Microseconds)
define BIN_1 900 //Binary 1 threshold (Microseconds)
define BIN_0 400 //Binary 0 threshold (Microseconds)

class IrReader { private:

boolean resultAvail;

int val, prevVal, pin, bitCount, result;
unsigned long startTime, elapsedTime;

public:

IrReader(int pin, int interruptNumber, void(*interruptCallback)( )) {
  this->pin = pin;
  pinMode(pin, INPUT);  
  prevVal = digitalRead(pin);
  bitCount = -1;
  resultAvail = false;

  attachInterrupt(interruptNumber, interruptCallback, CHANGE);      
}

boolean available() {
  return resultAvail;
}

int getKey() {
  resultAvail = false;
  return result;
}

void eval() {
  //Prevent reading a new result if an old result is still pending
  //(Could potentially miss a new key, but at least you won't get a garbage key)
  if (! resultAvail) {
    val = digitalRead(pin);

    if (val != prevVal) { //Value has changed
      prevVal = val;

      if (val == LOW) { //Falling value
        startTime = micros();
      } else { //Rising value - New Bit
        elapsedTime = micros() - startTime;

        if (elapsedTime >= START_BIT) {
          bitCount = 0;
          result = 0;
        } else if (bitCount != -1) {
          bitCount++;

          if(elapsedTime >= BIN_1) //Assume that anything shorter is a zero
            result |= (1 

