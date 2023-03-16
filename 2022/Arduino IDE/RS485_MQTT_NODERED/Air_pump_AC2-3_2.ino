//#include <SoftwareSerial.h>
//Create by Emag
//ESP32 get value rs485 from KP385 sent MQTT node-red
//DI TX2 , DE D5 , RE D4 , RO RX2
//Building A power
#include <ModbusMaster.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
//SoftwareSerial mySerial(2, 3); // RX, TX
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  1800        /* Time ESP32 will go to sleep (in seconds) */
RTC_DATA_ATTR int bootCount = 0;

#define MAX485_DE 5
#define MAX485_RE_NEG 4

ModbusMaster node;
const char* ssid = "DHAS-Handheld";
const char* password = "";

const char* mqtt_server = "10.4.200.7";
long last;
WiFiClient espClient;
PubSubClient client(espClient);
//*******************************************************************//
// Convent 32bit to float // ฟังชั่นแปลง 32bit ไปเป็น ทศนิยม *** เผื่อใช้
//*******************************************************************//
float HexTofloat(uint32_t x) {
  return (*(float*)&x);
}
uint32_t FloatTohex(float x) {
  return (*(uint32_t*)&x);
}// End

void preTransmission()
{
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

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
    if (client.connect("NO2-3")) {
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
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  // Init in receive mode

  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
  Serial.println("start init serial 0");
  Serial.begin(9600);
  while (!Serial) {
    Serial.println("loop for init serial 0");
  }
  Serial.println("start init software serial");
  Serial2.begin(9600);
  while (!Serial2) {
    Serial.println("loop for init software serial");
  }
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  //  node.begin(1, Serial2);
  //  node.preTransmission(preTransmission);
  //  node.postTransmission(postTransmission);

  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                 " Seconds");

  uint16_t result;
  uint32_t x;
  float currect;
  float power;
  for (int i = 1; i <= 2; i++) {
    node.begin(i, Serial2);
    node.preTransmission(preTransmission);
    node.postTransmission(postTransmission);
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    power = 0;
    Serial.println("Get data");
    result = node.readInputRegisters(0x0006, 0x0002);
    if (result == node.ku8MBSuccess)
    {
      Serial.print("currect: ");
      x = (node.getResponseBuffer(0) << 16) | node.getResponseBuffer(1);
      currect = HexTofloat(x);
      Serial.println(currect);
    }
    //delay(500);
    result = node.readInputRegisters(0x0048, 0x0002);
    if (result == node.ku8MBSuccess)
    {
      Serial.print("Voltage: ");
      x = (node.getResponseBuffer(0) << 16) | node.getResponseBuffer(1);
      power = HexTofloat(x);
      Serial.println(power);
    }

    char currectString[8];
    char powerString[8];
    dtostrf(currect, 1, 1, currectString);
    dtostrf(power, 1, 1, powerString);
    if (i == 1) {
      Serial.print("currect3: ");
      Serial.println(currectString);
      client.publish("esp32/currectNo3", currectString);
      Serial.print("powerNo3: ");
      Serial.println(powerString);
      client.publish("esp32/powerNo3", powerString);
    } else {
      Serial.print("currect2: ");
      Serial.println(currectString);
      client.publish("esp32/currectNo2", currectString);
      Serial.print("powerNo2: ");
      Serial.println(powerString);
      client.publish("esp32/powerNo2", powerString);
    }
  }
  Serial.println("Going to sleep now");
  Serial.flush();
  esp_deep_sleep_start();
}
void loop() {

}
