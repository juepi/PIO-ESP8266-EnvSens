# Introduction 
Environmental sensor utilizing the widely available [Bosch BME280 sensor](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/) based on my [ESP8266 Template](https://github.com/juepi/PIO-ESP8266-Template). The firmware will wake up the ESP after a configurable timespan (`include/generic-config.h`), read out temperature, humidity and air pressure from the BME280, send the values to the MQTT broker and go to sleep again.  
I'm using a single 26650 LFP cell for this setup (~11Wh) which lasts about 3-4 months when publishing sensor values every 15 minutes.

## Requirements
Please consult the README of my [ESP8266 Template](https://github.com/juepi/PIO-ESP8266-Template).  
To avoid power loss to the sensor and I2C pullup-resistors while the ESP is asleep, i've wired the VCC to `GPIO D3` (configurable in `user-config.h`), which will be set HIGH at firmware boot to power the sensor.

## Configuration
See file `include/user-config.h` for I/O pins and MQTT topics used to publish sensor data.

### MQTT Usage
Note that this sketch does not subscribe to user-defined topics (only to the ESP8266-Template default topics required for OTA flashing), it will only send the sensor data and status to the topics configured in `user-config.h`.

# Version History

## v1.0.0
- initial release