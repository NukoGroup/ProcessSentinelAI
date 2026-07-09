// ESP32 Firmware for ProcessSentinelAI
// MPU6050 Vibration, DS18B20 Temp, Flow Sensor
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <PubSubClient.h>

// WiFi and MQTT configs - FILL YOURS
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASS";
const char* mqtt_server = "YOUR_BROKER_IP";

Adafruit_MPU6050 mpu;
OneWire oneWire(4); // GPIO for DS18B20
DallasTemperature sensors(&oneWire);

WiFiClient espClient;
PubSubClient client(espClient);

// Flow sensor
const int flowPin = 5;
volatile int pulseCount = 0;

void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.begin();
  sensors.begin();
  pinMode(flowPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(flowPin), pulseCounter, FALLING);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  client.setServer(mqtt_server, 1883);
}

void loop() {
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  sensors_event_t a, g, temp_event;
  mpu.getEvent(&a, &g, &temp_event);
  float rms_vib = sqrt((a.acceleration.x*a.acceleration.x + a.acceleration.y*a.acceleration.y + a.acceleration.z*a.acceleration.z)/3.0);
  // Flow calc example
  float flowRate = pulseCount * 0.45; // calibrate factor
  pulseCount = 0;
  String payload = "{\"vib_rms\": " + String(rms_vib) + ", \"temp\": " + String(temp) + ", \"flow\": " + String(flowRate) + "}";
  client.publish("sensors/process1", payload.c_str());
  delay(1000);
}