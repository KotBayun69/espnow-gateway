#pragma once

#include <stdint.h>

// -------------------------------------------------------------------

#define ESPNOW_DEVICE_TYPE                       \
  DF(DT_NONE, "")                         \
  DF(DT_SENSOR, "espnow_sensor")          \
  DF(DT_BINARY_SENSOR, "espnow_sensor")        

typedef enum // Enumeration of device types supported by the ESP-NOW gateway.
{
#define DF(_value, _name) _value,
  ESPNOW_DEVICE_TYPE
#undef DF
} espnow_device_type_t;

/**
 * @brief Get char description from the enumeration device_type_t value.
 *
 * @note Used for identificate device type in MQTT topics (example - "homeassistant/espnow_switch/70-03-9F-44-BE-F7").
 *
 * @param[in] value Enumeration value of device_type_t.
 *
 * @return Pointer to char value
 */
char *get_device_type_value_name(espnow_device_type_t value);

// -------------------------------------------------------------------

#define ESPNOW_PAYLOAD_TYPE                    \
  DF(PLT_NONE, "")                      \
  DF(PLT_CONF,  "config")               \
  DF(PLT_STATE, "state")                \
  DF(PLT_BRIGHTNESS, "brightness")      \
  DF(PLT_TEMPERATURE, "temperature")    \
  DF(PLT_RGB, "rgb")                    \
  DF(PLT_EFFECT, "effect")                 

typedef enum // Enumeration of payload types.
{
#define DF(_value, _name) _value,
    ESPNOW_PAYLOAD_TYPE
#undef DF
} espnow_payload_type_t;

/**
 * @brief Get char description from the enumeration payload_type_t value.
 *
 * @note Used for identificate payload type in MQTT topics (example - "homeassistant/espnow_switch/70-03-9F-44-BE-F7/attributes").
 *
 * @param[in] value Enumeration value of payload_type_t.
 *
 * @return Pointer to char value
 */
char *get_payload_type_value_name(espnow_payload_type_t value);


// -------------------------------------------------------------------

#define HA_COMPONENT_TYPE                               \
    DF(HACT_NONE, "")                                   \
    DF(HACT_ALARM_CONTROL_PANEL, "alarm_control_panel") \
    DF(HACT_BINARY_SENSOR, "binary_sensor")             \
    DF(HACT_BUTTON, "button")                           \
    DF(HACT_CAMERA, "camera")                           \
    DF(HACT_COVER, "cover")                             \
    DF(HACT_DEVICE_TRACKER, "device_tracker")           \
    DF(HACT_FAN, "fan")                                 \
    DF(HACT_HUMIDIFIER, "humidifier")                   \
    DF(HACT_CLIMATE_HVAC, "climate")                    \
    DF(HACT_LIGHT, "light")                             \
    DF(HACT_LOCK, "lock")                               \
    DF(HACT_NUMBER, "number")                           \
    DF(HACT_SCENE, "scene")                             \
    DF(HACT_SELECT, "select")                           \
    DF(HACT_SENSOR, "sensor")                           \
    DF(HACT_SIREN, "siren")                             \
    DF(HACT_SWITCH, "switch")                           \
    DF(HACT_UPDATE, "update")                           \
    DF(HACT_TEXT, "text")                               \
    DF(HACT_VACUUM, "vacuum")                           \
    DF(HACT_MAX, "")

typedef enum // Enumeration of device types supported by the Home Assistant. For details see https://www.home-assistant.io/integrations/mqtt.
{
#define DF(_value, _name) _value,
    HA_COMPONENT_TYPE
#undef DF
} ha_component_type_t;

/**
 * @brief Get char description from the enumeration ha_component_type_t value.
 *
 * @note Used to prepare a configuration message for Home Assistant MQTT discovery.
 *
 * @param[in] value Enumeration value of ha_component_type_t.
 *
 * @return Pointer to char value
 */
char *get_component_type_value_name(ha_component_type_t value);

// ------------------------------------------------------------------

#define HA_BINARY_SENSOR_DEVICE_CLASS               \
    DF(HABSDC_NONE, "")                             \
    DF(HABSDC_BATTERY, "battery")                   \
    DF(HABSDC_BATTERY_CHARGING, "battery_charging") \
    DF(HABSDC_CARBON_MONOXIDE, "carbon_monoxide")   \
    DF(HABSDC_COLD, "cold")                         \
    DF(HABSDC_CONNECTIVITY, "connectivity")         \
    DF(HABSDC_DOOR, "door")                         \
    DF(HABSDC_GARAGE_DOOR, "garage_door")           \
    DF(HABSDC_GAS, "gas")                           \
    DF(HABSDC_HEAT, "heat")                         \
    DF(HABSDC_LIGHT, "light")                       \
    DF(HABSDC_LOCK, "lock")                         \
    DF(HABSDC_MOISTURE, "moisture")                 \
    DF(HABSDC_MOTION, "motion")                     \
    DF(HABSDC_MOVING, "moving")                     \
    DF(HABSDC_OCCUPANCY, "occupancy")               \
    DF(HABSDC_OPENING, "opening")                   \
    DF(HABSDC_PLUG, "plug")                         \
    DF(HABSDC_POWER, "power")                       \
    DF(HABSDC_PRESENCE, "presence")                 \
    DF(HABSDC_PROBLEM, "problem")                   \
    DF(HABSDC_RUNNING, "running")                   \
    DF(HABSDC_SAFETY, "safety")                     \
    DF(HABSDC_SMOKE, "smoke")                       \
    DF(HABSDC_SOUND, "sound")                       \
    DF(HABSDC_TAMPER, "tamper")                     \
    DF(HABSDC_UPDATE, "update")                     \
    DF(HABSDC_VIBRATION, "vibration")               \
    DF(HABSDC_WINDOW, "window")                     \
    DF(HABSDC_MAX, "")

typedef enum // Enumeration of binary sensor types supported by the Home Assistant. For details see https://www.home-assistant.io/integrations/binary_sensor/#device-class.
{
#define DF(_value, _name) _value,
    HA_BINARY_SENSOR_DEVICE_CLASS
#undef DF
} ha_binary_sensor_device_class_t;

/**
 * @brief Get char description from the enumeration ha_binary_sensor_device_class_t value.
 *
 * @note Used to prepare a configuration message for Home Assistant MQTT discovery.
 *
 * @param[in] value Enumeration value of ha_binary_sensor_device_class_t.
 *
 * @return Pointer to char value
 */
char *get_binary_sensor_device_class_value_name(ha_binary_sensor_device_class_t value);

// -------------------------------------------------------------------

#define HA_SENSOR_DEVICE_CLASS                                                                                                                                                                           \
    DF(HASDC_NONE, "")                                                                                                                                                                                   \
    DF(HASDC_APPARENT_POWER, "apparent_power")                                     /* Apparent power in VA */                                                                                            \
    DF(HASDC_AQI, "aqi")                                                           /* Air quality index (unitless) */                                                                                    \
    DF(HASDC_BATTERY, "battery")                                                   /* Percentage of battery that is left in % */                                                                         \
    DF(HASDC_CARBON_DIOXIDE, "carbon_dioxide")                                     /* Carbon dioxide in CO2 (Smoke) in ppm */                                                                            \
    DF(HASDC_CARBON_MONOXIDE, "carbon_monoxide")                                   /* Carbon monoxide in CO (Gas CNG/LPG) in ppm */                                                                      \
    DF(HASDC_CURRENT, "current")                                                   /* Current in A, mA */                                                                                                \
    DF(HASDC_DATE, "date")                                                         /* Date string (ISO 8601) */                                                                                          \
    DF(HASDC_DISTANCE, "distance")                                                 /* Generic distance in km, m, cm, mm, mi, yd, or in */                                                                \
    DF(HASDC_DURATION, "duration")                                                 /* Duration in d, h, min, or s */                                                                                     \
    DF(HASDC_ENERGY, "energy")                                                     /* Energy in Wh, kWh, MWh, MJ, or GJ */                                                                               \
    DF(HASDC_FREQUENCY, "frequency")                                               /* Frequency in Hz, kHz, MHz, or GHz */                                                                               \
    DF(HASDC_GAS, "gas")                                                           /* Gasvolume in m³, ft³ or CCF */                                                                                   \
    DF(HASDC_HUMIDITY, "humidity")                                                 /* Percentage of humidity in the air in % */                                                                          \
    DF(HASDC_ILLUMINANCE, "illuminance")                                           /* The current light level in lx */                                                                                   \
    DF(HASDC_MOISTURE, "moisture")                                                 /* Percentage of water in a substance in % */                                                                         \
    DF(HASDC_MONETARY, "monetary")                                                 /* The monetary value (ISO 4217) */                                                                                   \
    DF(HASDC_NITROGEN_DIOXIDE, "nitrogen_dioxide")                                 /* Concentration of nitrogen dioxide in µg/m³ */                                                                    \
    DF(HASDC_NITROGEN_MONOXIDE, "nitrogen_monoxide")                               /* Concentration of nitrogen monoxide in µg/m³ */                                                                   \
    DF(HASDC_NITROUS_OXIDE, "nitrous_oxide")                                       /* Concentration of nitrous oxide in µg/m³ */                                                                       \
    DF(HASDC_OZONE, "ozone")                                                       /* Concentration of ozone in µg/m³ */                                                                               \
    DF(HASDC_PM1, "pm1")                                                           /* Concentration of particulate matter less than 1 micrometer in µg/m³ */                                           \
    DF(HASDC_PM10, "pm10")                                                         /* Concentration of particulate matter less than 10 micrometers in µg/m³ */                                         \
    DF(HASDC_PM25, "pm25")                                                         /* Concentration of particulate matter less than 2.5 micrometers in µg/m³ */                                        \
    DF(HASDC_POWER_FACTOR, "power_factor")                                         /* Power factor (unitless), unit may be None or % */                                                                  \
    DF(HASDC_POWER, "power")                                                       /* Power in W or kW */                                                                                                \
    DF(HASDC_PRECIPITATION, "precipitation")                                       /* Accumulated precipitation in cm, in or mm */                                                                       \
    DF(HASDC_PRECIPITATION_INTENSITY, "precipitation_intensity")                   /* Precipitation intensity in in/d, in/h, mm/d or mm/h */                                                             \
    DF(HASDC_PRESSURE, "pressure")                                                 /* Pressure in Pa, kPa, hPa, bar, cbar, mbar, mmHg, inHg or psi */                                                    \
    DF(HASDC_REACTIVE_POWER, "reactive_power")                                     /* Reactive power in var */                                                                                           \
    DF(HASDC_SIGNAL_STRENGTH, "signal_strength")                                   /* Signal strength in dB or dBm */                                                                                    \
    DF(HASDC_SPEED, "speed")                                                       /* Generic speed in ft/s, in/d, in/h, km/h, kn, m/s, mph or mm/d */                                                   \
    DF(HASDC_SULPHUR_DIOXIDE, "sulphur_dioxide")                                   /* Concentration of sulphur dioxide in µg/m³ */                                                                     \
    DF(HASDC_TEMPERATURE, "temperature")                                           /* Temperature in °C, °F or K */                                                                                    \
    DF(HASDC_TIMESTAMP, "timestamp")                                               /* Datetime object or timestamp string (ISO 8601) */                                                                  \
    DF(HASDC_VOLATILE_ORGANIC_COMPOUNDS, "volatile_organic_compounds")             /* Concentration of volatile organic compounds in µg/m³ */                                                          \
    DF(HASDC_VOLTAGE, "voltage")                                                   /* Voltage in V, mV */                                                                                                \
    DF(HASDC_VOLUME, "volume")                                                     /* Generic volume in L, mL, gal, fl. oz., m³, ft³, or CCF */                                                        \
    DF(HASDC_WATER, "water")                                                       /* Water consumption in L, gal, m³, ft³, or CCF */                                                                  \
    DF(HASDC_WEIGHT, "weight")                                                     /* Generic mass in kg, g, mg, µg, oz, lb, or st */                                                                   \
    DF(HASDC_WIND_SPEED, "wind_speed")                                             /* Wind speed in Beaufort, ft/s, km/h, kn, m/s, or mph */                                                             \
    DF(HASDC_ATMOSPHERIC_PRESSURE, "atmospheric_pressure")                         /* Atmospheric pressure in cbar, bar, hPa, mmHg, inHg, kPa, mbar, Pa or psi */                                        \
    DF(HASDC_DATA_RATE, "data_rate")                                               /* Data rate in bit/s, kbit/s, Mbit/s, Gbit/s, B/s, kB/s, MB/s, GB/s, KiB/s, MiB/s or GiB/s */                        \
    DF(HASDC_DATA_SIZE, "data_size")                                               /* Data size in bit, kbit, Mbit, Gbit, B, kB, MB, GB, TB, PB, EB, ZB, YB, KiB, MiB, GiB, TiB, PiB, EiB, ZiB or YiB */ \
    DF(HASDC_ENERGY_STORAGE, "energy_storage")                                     /* Stored energy in Wh, kWh, MWh, MJ, or GJ */                                                                        \
    DF(HASDC_ENUM, "enum")                                                         /* Has a limited set of (non-numeric) states */                                                                       \
    DF(HASDC_IRRADIANCE, "irradiance")                                             /* Irradiance in W/m² or BTU/(h⋅ft²) */                                                                           \
    DF(HASDC_PH, "ph")                                                             /* Potential hydrogen (pH) value of a water solution */                                                               \
    DF(HASDC_SOUND_PRESSURE, "sound_pressure")                                     /* Sound pressure in dB or dBA */                                                                                     \
    DF(HASDC_VOLATILE_ORGANIC_COMPOUNDS_PARTS, "volatile_organic_compounds_parts") /* Ratio of volatile organic compounds in ppm or ppb */                                                               \
    DF(HASDC_VOLUME_FLOW_RATE, "volume_flow_rate")                                 /* Volume flow rate in m³/h, ft³/min, L/min, gal/min */                                                             \
    DF(HASDC_VOLUME_STORAGE, "volume_storage")                                     /* Generic stored volume in L, mL, gal, fl. oz., m³, ft³, or CCF */                                                 \
    DF(HASDC_MAX, "")

typedef enum // Enumeration of sensor types supported by the Home Assistant. For details see https://www.home-assistant.io/integrations/sensor.
{
#define DF(_value, _name) _value,
    HA_SENSOR_DEVICE_CLASS
#undef DF
} ha_sensor_device_class_t;

/**
 * @brief Get char description from the enumeration ha_sensor_device_class_t value.
 *
 * @note Used to prepare a configuration message for Home Assistant MQTT discovery.
 *
 * @param[in] value Enumeration value of ha_sensor_device_class_t.
 *
 * @return Pointer to char value
 */
char *get_sensor_device_class_value_name(ha_sensor_device_class_t value);

// -------------------------------------------------------------------

#define HA_ON_OFF_TYPE             \
    DF(HAONOFT_NONE, "")           \
    DF(HAONOFT_ON, "ON")           \
    DF(HAONOFT_OFF, "OFF")         \
    DF(HAONOFT_OPEN, "OPEN")       \
    DF(HAONOFT_CLOSE, "CLOSE")     \
    DF(HAONOFT_LOW, "LOW")         \
    DF(HAONOFT_MID, "MID")         \
    DF(HAONOFT_HIGH, "HIGH")       \
    DF(HAONOFT_ALARM, "ALARM")     \
    DF(HAONOFT_DRY, "DRY")         \
    DF(HAONOFT_MOTION, "MOTION")   \
    DF(HAONOFT_CONNECT, "CONNECT") \
    DF(HAONOFT_LEAKAGE, "LEAKAGE") \
    DF(HAONOFT_DETECTED, "DETECTED") \
    DF(HAONOFT_CLEARED, "CLEARED") \
    DF(HAONOFT_MAX, "")

typedef enum // Enumeration of payload_on / payload_off types supported by gateway.
{
#define DF(_value, _name) _value,
    HA_ON_OFF_TYPE
#undef DF
} ha_on_off_type_t;

/**
 * @brief Get char description from the enumeration ha_on_off_type_t value.
 *
 * @note Used to prepare a configuration message for Home Assistant MQTT discovery.
 *
 * @param[in] value Enumeration value of ha_on_off_type_t.
 *
 * @return Pointer to char value
 */
char *get_on_off_type_value_name(ha_on_off_type_t value);

// ------------------------------------------------------------------

#define HA_CHIP_TYPE              \
    DF(HACHT_NONE, "")            \
    DF(HACHT_ESP32, "ESP32")      \
    DF(HACHT_ESP8266, "ESP8266")  \
    DF(HACHT_ESP32S2, "ESP32-S2") \
    DF(HACHT_ESP32S3, "ESP32-S3") \
    DF(HACHT_ESP32C2, "ESP32-C2") \
    DF(HACHT_ESP32C3, "ESP32-C3") \
    DF(HACHT_ESP32C6, "ESP32-C6") \
    DF(HACHT_MAX, "")

typedef enum // Enumeration of ESP module types supported by gateway.
{
#define DF(_value, _name) _value,
    HA_CHIP_TYPE
#undef DF
} ha_chip_type_t;

/**
 * @brief Get char description from the enumeration ha_chip_type_t value.
 *
 * @note Used to prepare a attribytes message by ESP-NOW gateway.
 *
 * @param[in] value Enumeration value of ha_chip_type_t.
 *
 * @return Pointer to char value
 */
char *get_chip_type_value_name(ha_chip_type_t value);


// -------------------------------------------------------------------

#define HA_SENSOR_TYPE                                      \
    DF(HAST_NONE, "")                                       \
    DF(HAST_DS18B20, "DS18B20")                             \
    DF(HAST_AHT, "AHT") /* AHT10/AHT20/AHT21/AHT25/AHT30 */ \
    DF(HAST_SHT, "SHT") /* SHT2X/3X/4X */                   \
    DF(HAST_GATEWAY, "")                                    \
    DF(HAST_WINDOW, "")                                     \
    DF(HAST_DOOR, "")                                       \
    DF(HAST_LEAKAGE, "")                                    \
    DF(HAST_DHT, "DHT") /* DHT11/DHT22/AM2302/AM2320 */     \
    DF(HAST_BH1750, "BH1750")                               \
    DF(HAST_BMP280, "BMP280") /* BMP180/BMP280 */           \
    DF(HAST_BME280, "BME280")                               \
    DF(HAST_BME680, "BME680")                               \
    DF(HAST_HTU, "HTU") /* HTU20/HTU21/HTU30/HTU31 */       \
    DF(HAST_HDC1080, "HDC1080")                             \
    DF(HAST_MAX, "")

typedef enum // Enumeration of sensor / binary sensor supported by gateway.
{
#define DF(_value, _name) _value,
    HA_SENSOR_TYPE
#undef DF
} ha_sensor_type_t;

/**
 * @brief Get char description from the enumeration ha_sensor_type_t value.
 *
 * @note Used to prepare at attributes messages and status messages by ESP-NOW gateway.
 *
 * @param[in] value Enumeration value of ha_sensor_type_t.
 *
 * @return Pointer to char value
 */
char *get_sensor_type_value_name(ha_sensor_type_t value);

// ------------------------------------------------------------------------------

typedef struct { // Structure for data exchange between ESP-NOW devices.
    espnow_device_type_t device_type;
    espnow_payload_type_t payload_type;
    union {
        union {
            struct {                                                        // Structure of espnow_binary_sensor node configuration message. @note Used for publish at MQTT espnow_binary_sensor node configuration message.
                uint8_t unique_id;                                          // An ID that uniquely identifies this binary sensor device. @note The ID will look like this - "MAC-X" (for example 64-B7-08-31-00-A8-1). @attention If two binary sensors have the same unique ID, Home Assistant will raise an exception.
                ha_binary_sensor_device_class_t binary_sensor_device_class; // Binary sensor type supported by the Home Assistant. @note Used to prepare a correct configuration message for Home Assistant MQTT discovery. For details see https://www.home-assistant.io/integrations/binary_sensor.
                ha_on_off_type_t payload_on;                                // The payload that represents ON state.
                ha_on_off_type_t payload_off;                               // The payload that represents OFF state.
                uint16_t expire_after;                                      // If set, it defines the number of seconds after the sensors state expires, if its not updated. After expiry, the sensors state becomes unavailable.
                uint16_t off_delay;                                         // For sensors that only send on state updates (like PIRs), this variable sets a delay in seconds after which the sensors state will be updated back to off.
                bool enabled_by_default;                                    // Flag which defines if the entity should be enabled when first added.
                bool force_update;                                          // Sends update events (which results in update of state objects last_changed) even if the sensors state hasnt changed. Useful if you want to have meaningful value graphs in history or want to create an automation that triggers on every incoming state message (not only when the sensors new state is different to the current one).
                uint8_t qos;                                                // The maximum QoS level to be used when receiving and publishing messages.
                bool retain;                                                // If the published message should have the retain flag on or not.
                } binary_sensor_config_message;
            struct {                                          // Structure of espnow_sensor node configuration message. @note Used publish at MQTT espnow_sensor node configuration message.
                uint8_t unique_id;                            // An ID that uniquely identifies this sensor device. @note The ID will look like this - "MAC-X" (for example 64-B7-08-31-00-A8-1). @attention If two sensors have the same unique ID, Home Assistant will raise an exception.
                ha_sensor_device_class_t sensor_device_class; // Sensor type supported by the Home Assistant. @note Used to prepare a correct configuration message for Home Assistant MQTT discovery. For details see https://www.home-assistant.io/integrations/sensor.
                char unit_of_measurement[5];                  // Defines the units of measurement of the sensor, if any.
                uint8_t suggested_display_precision;          // The number of decimals which should be used in the sensors state after rounding.
                uint16_t expire_after;                        // If set, it defines the number of seconds after the sensors state expires, if its not updated. After expiry, the sensors state becomes unavailable.
                bool enabled_by_default;                      // Flag which defines if the entity should be enabled when first added.
                bool force_update;                            // Sends update events (which results in update of state objects last_changed) even if the sensors state hasnt changed. Useful if you want to have meaningful value graphs in history or want to create an automation that triggers on every incoming state message (not only when the sensors new state is different to the current one).
                uint8_t qos;                                  // The maximum QoS level to be used when receiving and publishing messages.
                bool retain;                                  // If the published message should have the retain flag on or not.
            } sensor_config_message;
        } config_message;
        union {
            struct { // Structure of espnow_binary_sensor node status message. @note Used for publish at MQTT espnow_binary_sensor node status message.
                ha_sensor_type_t sensor_type; // Binary sensor type. @note Used to identify the binary sensor type by ESP-NOW gateway and send the appropriate binary sensor status messages to MQTT.
                ha_on_off_type_t connect;     // Event that caused the sensor to be triggered (if present). @note Example - CONNECT @attention Must be same with set on binary_sensor_config_message structure.
                ha_on_off_type_t open;        // Event that caused the sensor to be triggered (if present). @note Example - OPEN / CLOSE @attention Must be same with set on binary_sensor_config_message structure.
                ha_on_off_type_t battery;     // Event that caused the sensor to be triggered (if present). @note Example - HIGH / LOW @attention Must be same with set on binary_sensor_config_message structure.
                ha_on_off_type_t leakage;     // Event that caused the sensor to be triggered (if present). @note Example - DRY / LEAKAGE @attention Must be same with set on binary_sensor_config_message structure.
                ha_on_off_type_t motion;      // Event that caused the sensor to be triggered (if present). @note Example - DETECTED / CLEARED @attention Must be same with set on binary_sensor_config_message structure.
                ha_on_off_type_t reserved_2;  // Reserved for future development.
            } binary_sensor_status_message;
            struct { // Structure of espnow_sensor node status message.
                ha_sensor_type_t sensor_type; // Sensor type. @note Used to identify the sensor type by ESP-NOW gateway and send the appropriate sensor status messages to MQTT.
                float temperature;            // Temperature value (if present).
                float humidity;               // Humidity value (if present).
                float atmospheric_pressure;   // Atmospheric pressure value (if present).
                float aqi;                    // Air quality index (if present).
                float voltage;                // Voltage value (if present).
                float illuminance;            // Light level (if present).
                float uv_index;               // UV index (if present).
                float reserved_3;             // Reserved for future development.
            } sensor_status_message;
        } status_message;
    } payload_data;
}  __attribute__((packed)) espnow_data_t;