/*
 * PIO-ESP8266-ENVSENS
 * ====================
 * Environmental sensor using ESP8266 + BME280
 */
#include "setup.h"

// Initialize Adafruit BME instance
Adafruit_BME280 bme;

/*
 * User Setup Loop
 * ========================================================================
 */
void user_setup()
{
  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);
}

/*
 * User Main Loop
 * ========================================================================
 */
void user_loop()
{
  static float QFE = 999.99;
  static float Temp = 12.34;
  static float RH = 54.32;

  // Enable power for BME
  pinMode(BME_VCC_PIN, OUTPUT);
  digitalWrite(BME_VCC_PIN, HIGH);
  delay(50);

  // Initialize sensor using default I2C address 0x76
  if (bme.begin(0x76, &Wire))
  {
    delay(50);
    // Gather data from BME (no error checking)..
#ifdef LOC_ALTITUDE
    QFE = bme.seaLevelForAltitude(LOC_ALTITUDE, bme.readPressure()) / 100.0F; // convert to hPa / mbar
#else
    QFE = bme.readPressure() / 100.0F;
#endif
    Temp = bme.readTemperature();
    RH = bme.readHumidity();
    DEBUG_PRINTLN("AirPress:" + String(QFE, 0));
    DEBUG_PRINTLN("Temp:" + String(Temp, 1));
    DEBUG_PRINTLN("RH:" + String(RH, 0));
    //..and publish to broker
    mqttClt.publish(t_temp, String(Temp, 1).c_str(), true);
    mqttClt.publish(t_humidity, String(RH, 0).c_str(), true);
    mqttClt.publish(t_airpress, String(QFE, 0).c_str(), true);
    mqttClt.publish(t_stat, String(s_Stat_Updated).c_str(), true);
  }
  else
  {
    DEBUG_PRINTLN("Could not initialize BME280 sensor!");
    DEBUG_PRINT("SensorID was: 0x");
    DEBUG_PRINTLN(bme.sensorID(), 16);
    mqttClt.publish(t_stat, String(s_Stat_SensFail).c_str(), true);
  }
}