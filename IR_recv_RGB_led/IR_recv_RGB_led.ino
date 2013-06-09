#include <IRremote.h>

long volPlus =  0x807F8877;
long volMinus = 0x807F08F7;
long mute =     0x807F40BF;
long input_up = 0x807F20DF;
long reset_dn = 0x807F10EF;
long treble_minus = 0x807FB04F;
long treble_plus  = 0x807F906F;
long bass_minus   = 0x807F708F;
long bass_plus    = 0x807F50AF;

int repeat   = 0xFFFFFFFF;

int REDpin = 3;
int GREENpin = 5;
int BLUEpin = 6;
int br = 0;
int incr  = 5;

boolean BLUEenabled = false;
boolean REDenabled =false;

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;


unsigned long previousMillis=0;

void setup(){
  pinMode(REDpin, OUTPUT);
  pinMode(GREENpin, OUTPUT);
  pinMode(BLUEpin, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == volPlus)
      BLUEenabled = true;
    if (results.value == volMinus)
      BLUEenabled = false;  
      
  if (results.value == mute)
      REDenabled = !REDenabled;;
      
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 30){
    previousMillis = currentMillis;
    br = br + incr;
    if (br <= 0 || br >= 100){
      incr = -incr;
    }
    
    br = constrain(br, 0, 100);
    if (BLUEenabled) 
      analogWrite(BLUEpin, br);
    else
      analogWrite(BLUEpin, 0);
    if (REDenabled) analogWrite(REDpin, br+155);
    else analogWrite(REDpin, 0);
    // analogWrite(GREENpin, br);
    //analogWrite(REDpin, br+155);
  }
}

