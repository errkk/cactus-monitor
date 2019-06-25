#include "main.h"

const char * HOST = "node-red.errkk.co";
const uint16_t PORT = 8888;

unsigned long previousMillisPublish = 0;
unsigned long previousMillisRead = 0;
uint16_t moisture;

void callback(char* topic, byte* payload, unsigned int length) {
}

void setup(void) {
    pinMode(A0, INPUT);
    pinMode(POWER_MOISTURE_SENSOR, OUTPUT);

    Serial.begin(115200);
    Serial.setTimeout(2000);
    setupWifi();
}

void loop(void) {
    moisture = readSensor();

    publish();
    delay(5000);
}

uint16_t readSensor() {
    digitalWrite(POWER_MOISTURE_SENSOR, HIGH);
    delay(500);
    uint16_t reading = analogRead(A0);
    delay(500);
    digitalWrite(POWER_MOISTURE_SENSOR, LOW);
    return reading;
}

void publish() {

    WiFiClient client;

    if (!client.connect(HOST, PORT)) {
        Serial.println("Couldn't connect");
        return;
    }
    Serial.print("Sending: ");
    Serial.println(moisture);
    client.print(moisture);
    client.stop();

    delay(1000);

    Serial.println("Going into deep sleep for a while");
    ESP.deepSleep(SLEEP_LONG);
}

void setupWifi() {
    delay(100);
    unsigned long wifiConnectStart = millis();

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(SSID);

    WiFi.begin(SSID, PSK);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if (millis() - wifiConnectStart > 15000) {
          Serial.println("Failed to connect to WiFi");
          return;
        }
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Netmask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
}
