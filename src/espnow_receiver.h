#include "settings.h"

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>
#include <SoftwareSerial.h>

// Create a struct_message called myData
struct_message myData;

// Initialize Softwareserial
SoftwareSerial softSerial(SOFT_RX, SOFT_TX);

// Send serial data to the gateway
void sendData() {
  softSerial.write((uint8_t*)&myData, sizeof(myData));
    
  // Toggle built-in LED to indicate activity
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    
  delay(10); // Small delay to prevent watchdog reset
}

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  
  memcpy(&myData, incomingData, sizeof(myData));

  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.a);
  Serial.print("Int: ");
  Serial.println(myData.b);
  Serial.print("Float: ");
  Serial.println(myData.c);
  Serial.print("Bool: ");
  Serial.println(myData.e);
  Serial.println();

  sendData();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.println();
  // Initialize Softwareserial Monitor
  softSerial.begin(BAUDRATE);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
}
  else {
    Serial.println("");
    Serial.println("ESP-NOW initialized successfully");
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  delay(1000);  // Delay to avoid flooding the Serial Monitor
}
