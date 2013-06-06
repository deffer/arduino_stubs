#include <IRremote.h>

int volPlus =  0x807F8877;
int volMinus = 0x807F08F7;
int mute =     0x807F40BF;
int input_up = 0x807F20DF;
int reset_dn = 0x807F10EF;
int treble_minus = 0x807FB04F;
int treble_plus  = 0x807F906F;
int bass_minus   = 0x807F708F;
int bass_plus    = 0x807F50AF;

int repeat   = 0xFFFFFFFF;


int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}

