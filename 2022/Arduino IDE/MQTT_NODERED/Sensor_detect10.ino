//Senser_detect
//Emag
// BME680
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme; // I2C
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  1800        /* Time ESP32 will go to sleep (in seconds) */
//RTC_DATA_ATTR int bootCount = 0;
//const char* ssid = "Printer";
const char* ssid = "DHAS-Handheld";
const char* password = "";

const char* mqtt_server = "10.4.200.7";
long last;
WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    long now = millis();
    if (now - last > 60000) {
      last = now;
      Serial.println("ESP_Restart");
      ESP.restart();
    }
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Environment 2")) {
      Serial.println("connected");
      // Subscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  while (!Serial);   // time to get serial running
  Serial.println(F("BME680 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }
  unsigned status;

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

//  ++bootCount;
//  Serial.println("Boot number: " + String(bootCount));
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                 " Seconds");

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  sensor();

  Serial.println("Going to sleep now");
  Serial.flush();
  esp_deep_sleep_start();
}
void loop() {
}
void sensor() {
  delay(1000);
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  float t = bme.temperature;
  float h = bme.humidity;

  char humidity[8];
  dtostrf(h, 1, 1, humidity);
  Serial.print("humidity: ");
  Serial.println(humidity);
  client.publish("esp32/humid2", humidity);

  char Temp[8];
  dtostrf(t, 1, 1, Temp);
  Serial.print("Temp: ");
  Serial.println(Temp);
  client.publish("esp32/temp2", Temp);
  delay(1000);
}
