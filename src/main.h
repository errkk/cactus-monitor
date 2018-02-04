#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "secrets.cpp"

#define POWER_MOISTURE_SENSOR 15
#define SLEEP_LONG 300e6
#define SLEEP_SHORT 5e6

uint16_t readSensor(void);
void setup(void);
void loop(void);
void setupWifi(void);
void callback(char* topic, byte* payload, unsigned int length);
void publish();
boolean connectToMQTT();