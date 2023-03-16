/*
  Controlling a servo position using a potentiometer (variable resistor)
  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

  modified on 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
Servo myservo;
Servo myservo1;
Servo myservo2;
Servo myservo3;

int pos = 90;
float pos1 = 87;
int pos2 = 110;
int pos3 = 70;

// create servo object to control a servo

void setup() {
  myservo.attach(8);  // attaches the servo on pin 9 to the servo object
  myservo1.attach(9);
  myservo2.attach(10);
  myservo3.attach(11);
  //Home
  myservo.write(90);                  // sets the servo position according to the scaled value
  myservo1.write(87);// Min 70 Max 87
  myservo2.write(110);
  myservo3.write(70);
  for (int A = 90; A < 122; A += 1) {
    myservo.write(A);
    delay(10);
    pos = A;
  }
  for (int A = 110; A < 142; A += 1) {
    myservo2.write(A);
    delay(10);
    pos2 = A;
  }
  for (int A = 70; A < 102; A += 1) {
    myservo3.write(A);
    delay(10);
    pos3 = A;
  }
}

void loop() {
  //  for (int pos = 70; pos < 87; pos += 1) {
  //    myservo1.write(pos);
  //    delay(50);
  //  }
  //  for (int pos = 87; pos > 70; pos -= 1) {
  //    myservo1.write(pos);
  //    delay(50);
  //  }
  for (int A = 64; A > 0; A -= 1) {
    pos1-=0.25;
    pos -= 1;
    pos2 -= 1;
    pos3 -= 1;
    myservo.write(pos);
    myservo1.write(pos1);
    myservo2.write(pos2);
    myservo3.write(pos3);
    delay(20);
  }
  for (int A = 0; A < 64; A += 1) {
    pos1+=0.25;
    pos += 1;
    pos2 += 1;
    pos3 += 1;
    myservo.write(pos);
    myservo1.write(pos1);
    myservo2.write(pos2);
    myservo3.write(pos3);
    delay(20);
  }

}
