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
const char* ssid = "Printer";
const char* password = "";

const char* mqtt_server = "10.4.200.7";

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
    if (client.connect("Building A")) {
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
  node.begin(1, Serial2);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                 " Seconds");

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  uint16_t result;
  uint32_t x;
  float power;
  Serial.println("Get data");
  result = node.readInputRegisters(0x0006, 0x0002);
  if (result == node.ku8MBSuccess)
  {
    Serial.print("Voltage: ");
    x = (node.getResponseBuffer(0) << 16) | node.getResponseBuffer(1);
    power = HexTofloat(x);
    Serial.println(power);
  }
  char powerString[8];
  dtostrf(power, 1, 1, powerString);
  Serial.print("currectA: ");
  Serial.println(powerString);
  client.publish("esp32/currectA", powerString);
  if (bootCount == 24) {
    bootCount = 0;
    Serial.println("Get datapower");
    result = node.readInputRegisters(0x0048, 0x0002);
    if (result == node.ku8MBSuccess)
    {
      Serial.print("Voltage: ");
      x = (node.getResponseBuffer(0) << 16) | node.getResponseBuffer(1);
      power = HexTofloat(x);
      Serial.println(power);
    }
    char powerString[8];
    dtostrf(power, 1, 1, powerString);
    Serial.print("powerA: ");
    Serial.println(powerString);
    client.publish("esp32/powerA", powerString);
  }
  Serial.println("Going to sleep now");
  Serial.flush();
  esp_deep_sleep_start();
}
void loop() {

}
