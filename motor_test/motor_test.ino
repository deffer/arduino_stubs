/*
Adafruit Arduino - Lesson 15. Bi-directional Motor
*/
 
int enablePin = 11;
int in1Pin = 10;
int in2Pin = 9;
int switchPin = 2;
int potPin = 0;
int ledPin = 13;
 
void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}
 
void loop()
{
  //int speed = analogRead(potPin) / 4;
  boolean reverse = digitalRead(switchPin);
  int speed = 125;
  setMotor(speed, reverse);
}
 
void setMotor(int speed, boolean reverse)
{
  analogWrite(enablePin, speed);
  digitalWrite(in1Pin, ! reverse);
  digitalWrite(in2Pin, reverse);
  digitalWrite(ledPin, reverse);
}
