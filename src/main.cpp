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
    Serial.setTimeout(2000);
    setupWifi();

    moisture = readSensor();
    Serial.println(moisture);

    if(connectToMQTT()) {
        publish();
        psClient.loop();
    }

    Serial.println("Going into deep sleep for a while");
    ESP.deepSleep(SLEEP_LONG);
}

void loop(void) {
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
    char cstr[16];
    itoa(moisture, cstr, 10);
    psClient.publish("cactus/moisture", cstr, true);
}

boolean connectToMQTT() {
    if (psClient.connect("arduinoClient", USERNAME, KEY)) {
        Serial.println("Connected to MQTT");
        return true;
    } else {
        Serial.println("Not connected to MQTT");
        return false;
    }
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
