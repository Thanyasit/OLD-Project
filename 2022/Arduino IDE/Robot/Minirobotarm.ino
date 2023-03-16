/*
  Controlling a servo position using a potentiometer (variable resistor)
  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

  modified on 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservor1;  // create servo object to control a servo
Servo myservor2;
Servo myservor3;


int val1;    // variable to read the value from the analog pin
int val2;
int val3;

void setup() {
  Serial.begin(9600);
  myservor1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservor2.attach(10);
  myservor3.attach(11);
  //Home
  myservor1.write(140);                  // sets the servo position according to the scaled value
  myservor2.write(10);
  myservor3.write(50);
}

void loop() {

  val1 = analogRead(A0);
  val2 = analogRead(A1);
  val3 = analogRead(A2);
  // print out the value you read:
  Serial.println(val1);
  Serial.println(val2);
  Serial.println(val3);
  val1 = map(val1, 1023, 550, 0, 180);
  val2 = map(val2, 0, 400, 10, 180);
  val3 = map(val3, 0, 750, 0, 180);
  myservor1.write(val1);                  // sets the servo position according to the scaled value
  myservor2.write(val2);
  myservor3.write(val3);
  //  delay(6000);
  //  myservo.write(180);                  // sets the servo position according to the scaled value
  //  //myservo.write(90);
  //  delay(3000);                           // waits for the servo to get there
}
