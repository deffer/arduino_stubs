/* Blink without Delay
 
 Turns on and off a light emitting diode(LED) connected to a digital  
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.
  
 created 2005
 by David A. Mellis
 modified 8 Feb 2010
 by Paul Stoffregen
 
 This example code is in the public domain.

 
 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 
 Code modified to demonstrate use of button to turn blinking routine on and off
 
 Circuit:
 LED attached ot pin 6 wiht 1 kOhm resistor between
 Button - pin2 to one leg -> connected leg - to 10 kOhm - to ground; opposite leg to 5V
 
 Expected behaviour:
 Start with long blinking external led once every 4 seconds
 Pressing button turns blinking routine off, leaving LED in last state (on or off)
 Internal LED (pin 13) is used for debugging and turned on when press is detected and routine is switched
 (turned off when button has been released)
 
 */

// constants won't change. Used here to set pin numbers:
const int ledPin =  6;      // the number of the LED pin
const int soundPin = 8;
const int switchPin = 2;

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
int soundState = LOW;
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 4000;           // interval at which to blink (milliseconds)
long blinkDuration = 500;

long off = 0; // whether blinking routine is on or off
long pressed = 0; // count ticks when button reads HIGH. once reached 50 assuming button was pressed (no mistake)

void setup() {  
  pinMode(switchPin,INPUT);
  pinMode(ledPin, OUTPUT);      
  pinMode(soundPin, OUTPUT);      
  
  // debug
  pinMode(13, OUTPUT);  
  digitalWrite(13, LOW);
  Serial.begin(9600);
}

void loop()
{  
  unsigned long currentMillis = millis();
  int sensorValue = digitalRead(switchPin);
  if (sensorValue == HIGH){       
    digitalWrite(13, HIGH);          
    if (pressed < 160)
      pressed = pressed+1;
    if (pressed == 150){      
      // switch to different mode
      if (off == 0) off = 1; else off = 0;
      Serial.print(off, DEC);  
    }
  }else{
    if (pressed > 0){
      pressed = 0;
      Serial.println();
      Serial.println("Release");      
    }
    digitalWrite(13, LOW);  
  }
 
  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.  
  if(currentMillis - previousMillis > interval) {
    // save the last time you started blinking the LED 
    previousMillis = currentMillis;   

  }else{
    if (currentMillis - previousMillis < blinkDuration && off == 0)  {
      ledState = LOW;
      soundState = LOW;
    }else if (currentMillis - previousMillis < blinkDuration*2 && off==0){
      soundState = LOW;      
      ledState = HIGH;
    }else if (off==0){
      ledState = HIGH;
      soundState = HIGH;      
    }
    
    
   digitalWrite(ledPin, ledState);
   digitalWrite(soundPin, soundState);
  }
}

