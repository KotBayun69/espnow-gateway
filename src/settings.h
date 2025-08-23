#include <stdint.h>
#include "credentials.h"

uint8_t broadcastAddress[] = {0xC4, 0x5B, 0xBE, 0x62, 0x13, 0xEC};

#define SOFT_RX D5  // GPIO14
#define SOFT_TX D6  // GPIO12

#define CHANNEL     0

#define BAUDRATE 9600

#define MQTT_HOST IPAddress(192, 168, 1, 101)
#define MQTT_PORT 1883
#define MQTT_TOPIC "HOMEASSISTANT/"

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    int b;
    float c;
    bool e;
} struct_message;