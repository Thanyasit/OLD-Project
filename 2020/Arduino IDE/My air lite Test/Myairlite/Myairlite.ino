#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
#include "PMS.h"
#include "BluetoothSerial.h"
unsigned long   time_now = 5000;
unsigned long show_now = 0;
int n = 0;
float PM = 0;
PMS pms(Serial);
PMS::DATA data;
Adafruit_BME280 bme; // I2C
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
void setup()
{
  Serial.begin(9600);
  SerialBT.begin("MyAir_Lite"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  delay(2000);
  pms.passiveMode();
  while (!Serial);   // time to get serial running
  //Serial.println(F("BME280 test"));
  unsigned status;
  // default settings
  status = bme.begin();
  // You can also pass in a Wire library object like &Wire2
  // status = bme.begin(0x76, &Wire2)
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    //while (1) delay(10);
  }
  pinMode(0, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(27, LOW);
  digitalWrite(14, LOW);
  digitalWrite(12, LOW);
  digitalWrite(4, LOW);
  digitalWrite(16, LOW);
  digitalWrite(33, LOW);
  digitalWrite(32, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  Serial.print("\n");
  Serial.print("Number\t");
  Serial.print("Humidity(bmp)%\t");
  Serial.print("Temperature(C)\t");
  Serial.print("Bug\t");
  Serial.print("PM 2.5(ug/m3)\t");
  Serial.println("Time");
}
void loop()
{
  if (millis() == time_now) {
    n++;
    Serial.print(n);
    Serial.print("\t\t");
    //pms.wakeUp();
    printValues();
    pms.requestRead();
    //Serial.print("\t\t");
    delay(250);
    if (pms.readUntil(data)) {
      Serial.println(data.PM_AE_UG_2_5);
      SerialBT.println(data.PM_AE_UG_2_5);
      //SerialBT.print(",");
    } else {
      Serial.println("No data.");
    }
    time_now = time_now + 5000;
  }
  if (digitalRead(0) == LOW) {
    show_now = millis();
    show_now = show_now + 5000;
    if (data.PM_AE_UG_2_5 <= 10) {
      digitalWrite(4, HIGH);
      digitalWrite(16, LOW);
      digitalWrite(33, LOW);
      digitalWrite(32, LOW);
      digitalWrite(25, LOW);
      digitalWrite(26, LOW);
    } else if (data.PM_AE_UG_2_5  <= 20) {
      digitalWrite(4, HIGH);
      digitalWrite(16, HIGH);
      digitalWrite(33, LOW);
      digitalWrite(32, LOW);
      digitalWrite(25, LOW);
      digitalWrite(26, LOW);
    } else if (data.PM_AE_UG_2_5  <= 37) {
      digitalWrite(4, HIGH);
      digitalWrite(16, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(32, LOW);
      digitalWrite(25, LOW);
      digitalWrite(26, LOW);
    } else if (data.PM_AE_UG_2_5 <= 50) {
      digitalWrite(4, HIGH);
      digitalWrite(16, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(25, LOW);
      digitalWrite(26, LOW);
    } else if (data.PM_AE_UG_2_5  <= 90) {
      digitalWrite(4, HIGH);
      digitalWrite(16, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(25, HIGH);
      digitalWrite(26, LOW);
    } else if (data.PM_AE_UG_2_5 > 91) {
      digitalWrite(4, HIGH);
      digitalWrite(16, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(32, HIGH);
      digitalWrite(25, HIGH);
      digitalWrite(26, HIGH);
    }
  }
  if (millis() == show_now) {
    digitalWrite(4, LOW);
    digitalWrite(16, LOW);
    digitalWrite(33, LOW);
    digitalWrite(32, LOW);
    digitalWrite(25, LOW);
    digitalWrite(26, LOW);
  }
}

void printValues() {
  Serial.print(bme.readHumidity());
  Serial.print("\t\t");
  SerialBT.print(bme.readHumidity());
  SerialBT.print(",");
  Serial.print(bme.readTemperature());
  Serial.print("\t\t");
  SerialBT.print(bme.readTemperature());
  SerialBT.print(",");
}
