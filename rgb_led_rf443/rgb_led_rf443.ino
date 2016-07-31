// left side: red - cathode/anode - green - blue
int REDpin = 3; // through 220Ohm
int GREENpin = 5; // through 180 Ohm
int BLUEpin = 6; // through 180 Ohm

// 8,9,10,11 - RF 


int incr  = 5;
// 0 - RED, 1 - BLUE, 2 - WHITE, 3 - GREEN, 4 - DARK
int modeColors[15] = {100,1,1, 1,1,100,  100,100,100, 1,100,1,  1,1,1};

void setup(){    
  pinMode(REDpin, OUTPUT);
  pinMode(GREENpin, OUTPUT);
  pinMode(BLUEpin, OUTPUT);

  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);  
  pinMode(11, INPUT);  
  
  //Serial.begin(9600);
}

void loop(){

  while (digitalRead(9) == LOW && digitalRead(10) == LOW && digitalRead(11) == LOW && digitalRead(8) == LOW) {
    showColorMode(4);  // Loops until button is pressed
  }  
    
  while (digitalRead(8) == HIGH) {  // Button 1 pressed
    showColorMode(0);
  }
  
  while (digitalRead(9) == HIGH) {  // Button 2 pressed
    showColorMode(1);
  }  
  
  while (digitalRead(10) == HIGH) {  // Button 3 pressed
    showColorMode(2);
  }
  
  while (digitalRead(11) == HIGH) {  // Button 4 pressed
    showColorMode(3);
  }
}

void showColorMode(int mode){
  analogWrite(REDpin, modeColors[mode*3]);
  analogWrite(GREENpin, modeColors[mode*3+1]);
  analogWrite(BLUEpin, modeColors[mode*3+2]);  
}

