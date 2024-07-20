/*
 *   ESP8266 Template
 *   Include all config files and Setup Function declarations
 */
#ifndef USER_SETUP_H
#define USER_SETUP_H

#include "mqtt-ota-config.h"

// Define required user libraries here
// Don't forget to add them into platformio.ini
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Declare user setup, main and custom functions
extern void user_setup();
extern void user_loop();

//
// MQTT Topics to publish sensor readings (publish only)
//
// main topic tree for all used MQTT topics (see also mqtt-ota-config.h)
#define TOPTREE "HB7/Outdoor/"
#define t_humidity TOPTREE "RH"
#define t_temp TOPTREE "Temp"
#define t_airpress TOPTREE "AirPress"
#define t_stat TOPTREE "Status"
#define s_Stat_Updated "DataUpdated" // string published to t_stat when sensor data has been published to the broker
#define s_Stat_SensFail "SensFail"   // string published to t_stat when sensor initialization failed

//
// BME280 related settings
//
#define I2C_SCL D1 // default I2C settings for D1 mini
#define I2C_SDA D2
#define BME_VCC_PIN D3      // GPIO used to power the BME sensor and pullup resistors; to avoid power drain while in deep_sleep
#define LOC_ALTITUDE 266.0F // local altitude for mean sea-level pressure calculation; unset for uncorrected pressure reading

#endif // USER_SETUP_H