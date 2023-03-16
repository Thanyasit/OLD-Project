#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);
volatile double waterFlow;
long last;
int setpoint = 0;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  digitalWrite(4, HIGH);

  Serial.begin(9600); //baudrate
  waterFlow = 0;
  attachInterrupt(15, pulse, RISING); //DIGITAL Pin 2: Interrupt 0

  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Flow     mL/sec");
  lcd.setCursor(4, 0);
  lcd.print(waterFlow);
  lcd.setCursor(0, 1);
  lcd.print("Setpoint = ");
  lcd.setCursor(11, 1);
  lcd.print(setpoint);
}

void loop() {
  long now = millis();
  if (now - last > 1000) {
    last = now;
    if (waterFlow < setpoint) {
      digitalWrite(4, LOW);
    } else {
      digitalWrite(4, HIGH);
    }
    Serial.print("waterFlow");
    Serial.print(waterFlow);
    Serial.println(" mL/sec");
    lcd.setCursor(4, 0);
    lcd.print("   ");
    lcd.setCursor(4, 0);
    lcd.print(waterFlow);
    lcd.setCursor(11, 1);
    lcd.print("     ");
    lcd.setCursor(11, 1);
    lcd.print(setpoint);
    waterFlow = 0;
  }
  if (digitalRead(19) == 0) {
    setpoint++;
    delay(100);
  } else if (digitalRead(18) == 0) {
    setpoint--;
    if (setpoint < 0) {
      setpoint = 0;
    }
    delay(100);
  }
  Serial.print("setpoint: ");
  Serial.println(setpoint);
}
void pulse() //measure the quantity of square wave
{
  waterFlow += 1.0 / 5.880;
}
