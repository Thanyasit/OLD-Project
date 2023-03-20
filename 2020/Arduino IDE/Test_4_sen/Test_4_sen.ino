#include "PMS.h"
#include <SDS011-select-serial.h>
#include <Arduino.h>
#include <sps30.h>
#include <hpma115S0.h>
unsigned long   time_now = 0;
PMS pms(Serial2);
PMS::DATA data;

float sdspm25 = 0;
float honeypm25 = 0;
HPMA115S0 hpma115S0(Serial1);

float p10, p25;
int error;
SDS011 my_sds(Serial3);


void setup() {
  int16_t ret;
  uint8_t auto_clean_days = 4;
  uint32_t auto_clean;
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  delay(5000);
  sensirion_i2c_init();
  ret = sps30_set_fan_auto_cleaning_interval_days(auto_clean_days);
  ret = sps30_start_measurement();
  hpma115S0.Init();
  hpma115S0.StartParticleMeasurement();
  Serial.println("LABEl,DATATIME,Sensirion,Honeywell,Plantower,Nova PM sensor");
  time_now = millis();
  time_now = time_now + 10000;
}

void loop() {
  struct sps30_measurement m;
  int16_t ret;
  ret = sps30_read_measurement(&m);
  unsigned int pm2_5, pm10;
  if (hpma115S0.ReadParticleMeasurement(&pm2_5, &pm10)) {
    //honeypm25 = pm2_5;
    //Serial.println(String(pm2_5));
  }
  pms.read(data);
  error = my_sds.read(&p25, &p10);
  if (! error) {
    sdspm25 = p25;
  }
  delay(1000);
  if (millis() >= time_now) {
    Serial.print("DATA,TIME");
    Serial.print(",");
    Serial.print(m.mc_2p5);
    Serial.print(",");
    Serial.print(String(pm2_5));
    Serial.print(",");
    Serial.print(data.PM_AE_UG_2_5);
    Serial.print(",");
    Serial.println(String(sdspm25));
    time_now = millis();
    time_now = time_now + 15000;
  }
}
