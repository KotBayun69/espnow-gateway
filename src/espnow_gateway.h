#include "settings.h"

#include <ESP8266WiFi.h>
#include <AsyncMqttClient.h>
#include <SoftwareSerial.h>
#include <Ticker.h>

SoftwareSerial softSerial(SOFT_RX, SOFT_TX);

struct EspNowMessage {
  uint32_t counter;
  char payload[32];
};

EspNowMessage message;
AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;
Ticker wifiReconnectTimer;
bool mqttConnected = false;  // Track connection state
// Define WiFi event handlers
WiFiEventHandler gotIpEventHandler, disconnectedEventHandler;

void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void connectToMqtt() {
  if (WiFi.isConnected() && !mqttConnected) {
    Serial.println("Connecting to MQTT...");
    mqttClient.connect();
  }
}

void onStationModeGotIP(const WiFiEventStationModeGotIP& event) {
  Serial.print("WiFi connected. IP: ");
  Serial.println(event.ip);
  connectToMqtt();
}

void onStationModeDisconnected(const WiFiEventStationModeDisconnected& event) {
  Serial.println("WiFi lost connection");
  mqttConnected = false;
  mqttReconnectTimer.detach();
  wifiReconnectTimer.once(2, connectToWifi);
}

void onMqttConnect(bool sessionPresent) {
  mqttConnected = true;
  Serial.println("MQTT connected");
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  mqttConnected = false;
  Serial.print("MQTT disconnected. Reason: ");
  Serial.println(static_cast<int>(reason));
  
  if (reason == AsyncMqttClientDisconnectReason::TCP_DISCONNECTED) {
    Serial.println("TCP disconnect - will reconnect");
  }
  
  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(5000, connectToMqtt);  // Wait 5 seconds
  }
}

void setup() {
  Serial.begin(115200);
  softSerial.begin(BAUDRATE);
  
  // Enable pull-ups for SoftwareSerial stability
  pinMode(SOFT_RX, INPUT_PULLUP);
  
  // Configure WiFi with event handlers
  gotIpEventHandler = WiFi.onStationModeGotIP(&onStationModeGotIP);
  disconnectedEventHandler = WiFi.onStationModeDisconnected(&onStationModeDisconnected);
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  
  // Configure MQTT client with credentials
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCredentials(MQTT_USER, MQTT_PASSWORD);  // Add authentication
  mqttClient.setClientId("ESP-NOW-Gateway");  // Unique client ID
  
  // Start connection sequence
  Serial.println("\nInitializing...");
  connectToWifi();
}

void loop() {
  // Handle incoming serial data
  if (softSerial.available() >= (int) sizeof(message)) {
    softSerial.readBytes((char*)&message, sizeof(message));
    
    Serial.print("Received: ");
    Serial.println(message.payload);
    
    if (mqttConnected) {
      String payload = String("{\"counter\":") + message.counter 
                     + ",\"data\":\"" + message.payload + "\"}";
      mqttClient.publish(MQTT_TOPIC, 1, true, payload.c_str());
      Serial.println("Published to MQTT");
    } else {
      Serial.println("MQTT not connected. Message discarded");
    }
  }
  delay(5000);  // Adjust delay as needed
  if (mqttConnected) {
      String payload = String("Test message at ") + millis();
      mqttClient.publish(MQTT_TOPIC, 1, false, payload.c_str());
      Serial.println("Published to MQTT");
    } else {
      Serial.println("MQTT not connected. Message discarded");
    }

  // Periodic connection check
  static unsigned long lastCheck = 0;
  if (millis() - lastCheck > 10000) {
    lastCheck = millis();
    
    if (!WiFi.isConnected()) {
      Serial.println("Reconnecting WiFi...");
      connectToWifi();
    }
    else if (!mqttConnected) {
      Serial.println("Reconnecting MQTT...");
      connectToMqtt();
    }
  }
}