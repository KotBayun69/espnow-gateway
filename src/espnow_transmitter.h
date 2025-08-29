#include "settings.h"

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

// Create a struct_message called myData
EspNowMessage myData;

unsigned long lastSendTime = 0;  
const unsigned long sendInterval = 10000;  // send readings timer
int testCounter = 0;


// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
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

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  // Initialize the message structure with dummy data
  strcpy(myData.device_id, "test_sensor");
  strcpy(myData.device_name, "Test Sensor");
  myData.rssi = -65;
  myData.battery = 85;

  // Verify structure size
  Serial.print("Message size: ");
  Serial.print(sizeof(EspNowMessage));
  Serial.println(" bytes");
  
  Serial.println("ESP-NOW Dummy Data Transmitter");
  Serial.println("==============================");
}
 
void loop() {
  if ((millis() - lastSendTime) >= sendInterval) {
    lastSendTime = millis();
    testCounter++;

    // Dummy Temperature sensor
    strcpy(myData.data.sensor_type, "temperature");
    dtostrf(20.0 + (random(0, 200) / 10.0), 1, 1, myData.data.state); // 20.0-40.0°C
    strcpy(myData.data.device_class, "temperature");
    strcpy(myData.data.unit, "°C");

    // Update timestamp
    myData.timestamp = millis();

    // Print debug info
    Serial.print("Sent test message #");
    Serial.print(testCounter);
    Serial.print(": ");
    Serial.print(myData.data.sensor_type);
    Serial.print(" = ");
    Serial.print(myData.data.state);
    Serial.println(myData.data.unit);

    // Send message via ESP-NOW
   int sendStatus = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

   if (sendStatus == 0) {
      Serial.println("Send success");
    } else {
      Serial.print("Send error: ");
      Serial.println(sendStatus);
    }

    // Toggle built-in LED to indicate transmission
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  
  delay(10); // Small delay to prevent watchdog reset

    
}
