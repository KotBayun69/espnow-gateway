#include "settings.h"
#ifdef GETMACADDRESS
  #include "get_mac_address.h"
#endif
/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <esp_now.h>

// Create a struct_message called myData
EspNowMessage myData;

unsigned long lastSendTime  = 0;  
const unsigned long sendInterval  = 5000;  // send readings timer
int testCounter = 0; 

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  // esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
}
 
void loop() {
  checkDataSize();
  delay(5000);
  // if (millis() - lastSendTime >= sendInterval) {
  //   lastSendTime = millis();
  //   testCounter++;
    
  //   // Temperature sensor
  //   myData.sensor_count = 1;
  //   strcpy(myData.data[0].sensor_type, "temperature");
  //   dtostrf(20.0 + (random(0, 200) / 10.0), 1, 1, myData.data[0].state); // 20.0-40.0°C
  //   strcpy(myData.data[0].device_class, "temperature");
  //   strcpy(myData.data[0].unit, "°C");

  //   // Update timestamp
  //   myData.timestamp = millis();
    
  //   // Print debug info
  //   Serial.print("Sent test message #");
  //   Serial.print(testCounter);
  //   Serial.print(" with ");
  //   Serial.print(myData.sensor_count);
  //   Serial.println(" sensors");
    
  //   for (int i = 0; i < myData.sensor_count; i++) {
  //     Serial.print("  ");
  //     Serial.print(myData.data[i].sensor_type);
  //     Serial.print(": ");
  //     Serial.print(myData.data[i].state);
  //     Serial.print(" ");
  //     Serial.println(myData.data[i].unit);
  //   }

  //   // Send message via ESP-NOW
  //   esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  //   // Toggle built-in LED to indicate transmission
  //   digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  //   lastSendTime = millis();

    // delay(10); // Small delay to prevent watchdog reset
  // }
}
