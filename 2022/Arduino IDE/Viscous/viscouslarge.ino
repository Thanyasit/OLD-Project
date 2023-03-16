#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
volatile int NbTopsFan; //measuring the rising edges of the signal
int Calc;
int hallsensor = 2;    //The pin location of the sensor
int setpoint = 0;
void rpm()     //This is the function that the interupt calls
{
  NbTopsFan++;  //This function measures the rising and falling edge of the hall effect sensors signal
}

void setup() //
{
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
  Serial.begin(9600); //This is the setup function where the serial port is initialised,
  attachInterrupt(0, rpm, RISING); //and the interrupt is attached
  digitalWrite(6, HIGH);

  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Flow     L/hour");
  lcd.setCursor(4, 0);
  lcd.print(Calc);
  lcd.setCursor(0, 1);
  lcd.print("Setpoint = ");
  lcd.setCursor(11, 1);
  lcd.print(setpoint);
}



void loop()
{
  NbTopsFan = 0;   //Set NbTops to 0 ready for calculations
  sei();      //Enables interrupts
  if (digitalRead(4) == 0) {
    setpoint++;
    delay(150);
  } else if (digitalRead(5) == 0) {
    setpoint--;
    if (setpoint < 0) {
      setpoint = 0;
    }
    delay(150);
  }
  if (Calc < setpoint) {
    digitalWrite(6, LOW);
  } else {
    digitalWrite(6, HIGH);
  }
  Serial.print("setpoint: ");
  Serial.println(setpoint);
  lcd.setCursor(4, 0);
  lcd.print("    ");
  lcd.setCursor(5, 0);
  lcd.print(Calc);
  lcd.setCursor(11, 1);
  lcd.print("     ");
  lcd.setCursor(11, 1);
  lcd.print(setpoint);
  delay(100);   //Wait 1 second
  cli();      //Disable interrupts
  Calc = (NbTopsFan * 60 / 7.5); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/hour
  Serial.print(Calc, DEC); //Prints the number calculated above
  Serial.println(" L/hour"); //Prints "L/hour" and returns a new line
}
