#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
#include "PMS.h"
#include "BluetoothSerial.h"
PMS pms(Serial);
PMS::DATA data;
Adafruit_BME280 bme; // I2C
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
void setup() {
  Serial.begin(9600);
  SerialBT.begin("MyAir_Lite"); //Bluetooth device name
  pms.passiveMode();
  pms.wakeUp();
  delay(2000);
  while (!Serial);
  unsigned status;
  status = bme.begin();
  printValues();
  pms.requestRead();
  delay(250);
  if (pms.readUntil(data)) {
    Serial.print(data.PM_AE_UG_2_5);
    SerialBT.println(data.PM_AE_UG_2_5);
  } else {
    Serial.print("No data.");
  }
  Serial.print("\t\t");
  pms.sleep();
  esp_sleep_enable_timer_wakeup(15 * 1000 * 1000); // กำหนดให้ตื่นเมื่อครบ 15 วินาทีข้างหน้า
  esp_deep_sleep_start(); // เริ่มเข้าสู่โหมด Deep Sleep
}
void loop() {
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
