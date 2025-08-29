#include "credentials.h"
#include "espnow_config.h"
#include <ArduinoJson.h>
#ifdef ESP32
  #include <esp_now.h>
  #include <WiFi.h>
  #define error_t esp_err_t
#endif
#ifdef ESP8266
  #include <ESP8266WiFi.h>
  #include <espnow.h>
  #define esp_error_t int
#endif


uint8_t broadcastAddress[] = {0xC4, 0x5B, 0xBE, 0x62, 0x13, 0xEC};

#define SOFT_RX D5  // GPIO14
#define SOFT_TX D6  // GPIO12

#define CHANNEL     0

#define BAUDRATE 4800

#define MQTT_HOST IPAddress(192, 168, 1, 101)
#define MQTT_PORT 1883
#define MQTT_TOPIC "homeassistant"

#define MAX_ESP_NOW_DATA_SIZE 208