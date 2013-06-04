int counter = 0;

void setup() {
  Serial.begin(9600);
pinMode(2,INPUT_PULLUP);
pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
  int sensorValue = digitalRead(2);
  Serial.print(sensorValue, DEC);  
  if (counter>50){
    Serial.println();
    counter = 0;
  }else{    
    counter ++;
  }  
  //Serial.println(sensorValue, DEC);
}
