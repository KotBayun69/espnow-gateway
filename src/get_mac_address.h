// /*
//   Rui Santos & Sara Santos - Random Nerd Tutorials
//   Complete project details at https://RandomNerdTutorials.com/get-change-esp32-esp8266-mac-address-arduino/
//   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.  
//   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// */
// #ifdef esp12e
// #include <ESP8266WiFi.h>
// #else
// #include <WiFi.h>
// #endif
#ifndef Serial
#include <Arduino.h>
#endif

#ifndef WiFi
  #ifdef esp12e
    #include <ESP8266WiFi.h>
  #endif
  #ifdef esp32
    #include <WiFi.h>
  #endif
#endif

void getMacAddress(){
  Serial.println();
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
}

void checkDataSize() {
  Serial.print("New structure size: ");
  Serial.print(sizeof(EspNowMessage));
  Serial.println(" bytes");
  
  // ESP-NOW max size is 250 bytes
  if (sizeof(EspNowMessage) > 250) {
    Serial.println("WARNING: Data structure too large for ESP-NOW!");
  }
}