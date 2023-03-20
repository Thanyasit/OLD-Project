#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
#include "PMS.h"
#include "BluetoothSerial.h"
unsigned long   time_now = 0;
unsigned long show_now = 0;
unsigned long send_now = 3000;
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
  pms.passiveMode();
  pms.wakeUp();
  delay(2000);
  while (!Serial);   // time to get serial running
  unsigned status;
  status = bme.begin();
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
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
  digitalWrite(14, HIGH);
  time_now = millis();
  time_now = time_now + 180000;
}
void loop()
{
  if (millis() == send_now) {
    SerialBT.print(bme.readHumidity());
    SerialBT.print(",");
    SerialBT.print(bme.readTemperature());
    SerialBT.print(",");
    pms.requestRead();
    delay(250);
    if (pms.readUntil(data)) {
      SerialBT.println(data.PM_AE_UG_2_5);
    } else {
      SerialBT.println("Error");
    }
    send_now = send_now + 3000;
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
  if (millis() == time_now ) {
    pms.sleep();
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0); // กำหนดขาที่ต่อกับเซ็นเซอร์ และกำหนด Active เป็น LOW
    esp_deep_sleep_start();
  }
}
