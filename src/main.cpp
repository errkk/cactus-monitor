#include "main.h"

const char * HOST = "node-red.errkk.co";
const uint16_t PORT = 8888;

uint16_t reading;

void callback(char* topic, byte* payload, unsigned int length) {
}

void setup(void) {
    pinMode(A0, INPUT);
    Serial.begin(115200);
    Serial.setTimeout(2000);
    setupWifi();
}

void loop(void) {
    reading = readSensor();

    publish();
    delay(5000);
}

uint16_t readSensor() {
    uint16_t reading = analogRead(A0);
    long ua = map(reading, 0, 1024, 0, 18500);
    Serial.print("Ma: ");
    Serial.print(ua/1000.0);
    Serial.print(" ADC: ");
    Serial.println(reading);
    delay(100);
    return reading;
}

void publish() {
    WiFiClient client;

    if (!client.connect(HOST, PORT)) {
        Serial.println("Couldn't connect");

        Serial.println("Snoozing for a restart");
        ESP.deepSleep(SLEEP_SHORT);
        return;
    }
    Serial.print("Sending: ");
    Serial.println(reading);
    client.print(reading);
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
