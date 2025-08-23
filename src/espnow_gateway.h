#include "settings.h"

#include <ESP8266WiFi.h>
#include <AsyncMqttClient.h>
#include <SoftwareSerial.h>
#include <Ticker.h>
#include <time.h>

// NTP Configuration
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3;       // Adjust for your timezone
const int daylightOffset_sec = 3600; // 3600 for DST in seconds
const unsigned long ntpSyncInterval = 3600000; // Sync time every hour

// Time management
unsigned long lastNtpSync = 0;
bool timeSynced = false;
unsigned long systemStartTime = 0;

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
  Serial.println("Gateway ready. Waiting for sensor data...");
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

bool syncTime() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  // Wait for time to be synchronized
  int retries = 0;
  while (retries < 10) {
    time_t now = time(nullptr);
    if (now > 1000000000) { // Check if we have a valid timestamp (after 2001)
      timeSynced = true;
      Serial.println("Time synchronized successfully");
      return true;
    }
    delay(1000);
    retries++;
  }
  
  Serial.println("Failed to synchronize time");
  timeSynced = false;
  return false;
}

String getTimestamp() {
  if (timeSynced) {
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    
    char timeString[25];
    strftime(timeString, sizeof(timeString), "%Y-%m-%dT%H:%M:%SZ", timeinfo);
    return String(timeString);
  } else {
    // Fallback: use system uptime
    unsigned long uptime = (millis() - systemStartTime) / 1000;
    return "Uptime:" + String(uptime) + "s";
  }
}

void setup() {
  Serial.begin(115200);
  softSerial.begin(BAUDRATE);

  // Record system start time for uptime fallback
  systemStartTime = millis();
  
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
  connectToMqtt();

  // Initial time sync
  if (WiFi.status() == WL_CONNECTED) {
    syncTime();
  }
}

void loop() {
  uint8_t qos = 1;
  bool retain = true;
  // Handle incoming serial data
  if (softSerial.available() >= (int) sizeof(message)) {
    softSerial.readBytes((char*)&message, (size_t) sizeof(message));
    
    Serial.print("Received: ");
    Serial.println(message.payload);
    
    if (mqttConnected) {
      String payload = String("{\"counter\":") + message.counter 
                     + ",\"data\":\"" + message.payload + "\"}";
      mqttClient.publish(MQTT_TOPIC, qos, retain, payload.c_str());
      Serial.println("Published to MQTT");
    } else {
      Serial.println("MQTT not connected. Message discarded");
    }
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

  // Regular time synchronization
  if (WiFi.status() == WL_CONNECTED && millis() - lastNtpSync > ntpSyncInterval) {
    syncTime();
    lastNtpSync = millis();
  }
}