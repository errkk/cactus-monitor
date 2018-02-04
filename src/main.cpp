#include "main.h"

WiFiClient wifiClient;
PubSubClient psClient(SERVER, SERVERPORT, callback, wifiClient);

unsigned long previousMillisPublish = 0;
unsigned long previousMillisRead = 0;
uint16_t moisture;

void callback(char* topic, byte* payload, unsigned int length) {
}

void setup(void) {
    pinMode(A0, INPUT);
    pinMode(POWER_MOISTURE_SENSOR, OUTPUT);
    Serial.begin(115200);
    setupWifi();

    if (psClient.connect("arduinoClient", USERNAME, KEY)) {
        Serial.println("Connected to MQTT");
    } else {
        Serial.println("Not connected to MQTT");
    }
}

uint16_t readSensor(unsigned long interval) {
    unsigned long currentMillis = millis();

    if ((unsigned long)(currentMillis - previousMillisRead) <= interval) {
      return moisture;
    }

    previousMillisRead = currentMillis;

    digitalWrite(POWER_MOISTURE_SENSOR, HIGH);
    delay(500);
    uint16_t reading = analogRead(A0);
    delay(500);
    digitalWrite(POWER_MOISTURE_SENSOR, LOW);
    return reading;
}

void loop(void) {
    moisture = readSensor(5000);
    publish(5000);
    Serial.println(moisture);
    psClient.loop();
}

void publish(unsigned long interval) {
    unsigned long currentMillis = millis();

    if ((unsigned long)(currentMillis - previousMillisPublish) <= interval) {
      return;
    }

    previousMillisPublish = currentMillis;

    char cstr[16];
    itoa(moisture, cstr, 10);
    psClient.publish("cactus/moisture", cstr);
}

void setupWifi() {
    delay(100);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(SSID);

    WiFi.begin(SSID, PSK);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
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
