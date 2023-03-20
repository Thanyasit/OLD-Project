#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
#include "PMS.h"
unsigned long   time_now = 10000;
int n = 0;
PMS pms(Serial);
PMS::DATA data;
Adafruit_BME280 bme; // I2C
int UVOUT = A0; //Output from the sensor
int REF_3V3 = A1; //3.3V power on the Arduino board
void setup()
{
  Serial.begin(9600);
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
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
  /*
  Serial.print("\n");
  Serial.print("Number\t");
  Serial.print("UV_Intensity(mW/cm^2)\t");
  Serial.print("Humidity(bmp)%\t");
  Serial.print("Temperature(C)\t");
  Serial.print("Pressure(hPa)\t");
  Serial.print("Approx. Altitude(m)\t");
  Serial.print("Error\t");
  Serial.print("PM 2.5(ug/m3)\t");
  Serial.println("Time");
  */
}
void loop()
{
  if (millis() == time_now) {
    int uvLevel = averageAnalogRead(UVOUT);
    int refLevel = averageAnalogRead(REF_3V3);
    float outputVoltage = 3.3 / refLevel * uvLevel;
    float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level
    n++;
    Serial.print("DATA,TIME");
    Serial.print(",");
    Serial.print(uvIntensity);
    Serial.print(",");
    printValues();
    pms.requestRead();
    Serial.print(",");
    if (pms.readUntil(data)) {
      Serial.print(data.PM_AE_UG_2_5);
    } else {
      Serial.print("No data.");
    }
    Serial.print(",");
    //delay(delayTime);
    Serial.println(time_now);
    time_now = time_now + 10000;
  }
}
void printValues() {
  Serial.print(bme.readHumidity());
  Serial.print(",");
  Serial.print(bme.readTemperature());
  Serial.print(",");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.print(",");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.print(",");
}
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0;

  for (int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
  return (runningValue);
}
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
