/* Blink without Delay
 
 Turns on and off a light emitting diode(LED) connected to a digital  
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.
 
 The circuit:
 * LED attached from pin 13 to ground.
 * Note: on most Arduinos, there is already an LED on the board
 that's attached to pin 13, so no hardware is needed for this example.
 
 
 created 2005
 by David A. Mellis
 modified 8 Feb 2010
 by Paul Stoffregen
 
 This example code is in the public domain.

 
 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */

// constants won't change. Used here to 
// set pin numbers:
const int ledPin =  6;      // the number of the LED pin
const int soundPin = 8;

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
int soundState = LOW;
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 4000;           // interval at which to blink (milliseconds)
long blinkDuration = 500;


void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);      
  pinMode(soundPin, OUTPUT);      
}

void loop()
{
  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you started blinking the LED 
    previousMillis = currentMillis;   

  }else{
    if (currentMillis - previousMillis < blinkDuration)  {
      ledState = LOW;
      soundState = LOW;
    }else if (currentMillis - previousMillis < blinkDuration*2){
      soundState = LOW;      
      ledState = HIGH;
    }else{
      ledState = HIGH;
      soundState = HIGH;      
    }
    
    
   digitalWrite(ledPin, ledState);
   digitalWrite(soundPin, soundState);
  }
}

