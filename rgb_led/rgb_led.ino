int REDpin = 3;
int GREENpin = 5;
int BLUEpin = 6;
int br = 0;
int incr  = 5;

void setup(){
  pinMode(REDpin, OUTPUT);
  pinMode(GREENpin, OUTPUT);
  pinMode(BLUEpin, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  br = br + incr;
  if (br <= 0 || br >= 255){
    incr = -incr;
  }
  
  br = constrain(br, 0, 255);
  analogWrite(REDpin, br);
  analogWrite(GREENpin, constrain(br, 0, 10));
  analogWrite(BLUEpin, br);
  
  delay(20);
}

