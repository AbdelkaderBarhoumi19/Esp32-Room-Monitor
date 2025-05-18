#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include "DHT.h"

// === DHT11 Configuration ===
#define DHTPIN 4          // GPIO connected to DHT11 data pin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// === BMP280 Configuration ===
Adafruit_BMP280 bmp;      // I2C Interface

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize DHT11
  dht.begin();

  // Initialize BMP280
  if (!bmp.begin(0x76)) {  // Try 0x77 if 0x76 doesn't work
    Serial.println("Erreur : BMP280 non détecté !");
    while (1);
  }

  Serial.println("DHT11 et BMP280 initialisés !");
}

void loop() {
  // Read DHT11 data
  float humidity = dht.readHumidity();
  float temp_dht = dht.readTemperature();  // °C

  // Read BMP280 data
  float temp_bmp = bmp.readTemperature();  // °C
  float pressure = bmp.readPressure() / 100.0F;  // Convert Pa to hPa

  // Check for failed readings
  if (isnan(humidity) || isnan(temp_dht)) {
    Serial.println("Erreur de lecture du DHT11 !");
  } else {
    Serial.print("DHT11 - Température: ");
    Serial.print(temp_dht);
    Serial.print(" °C | Humidité: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  Serial.print("BMP280 - Température: ");
  Serial.print(temp_bmp);
  Serial.print(" °C | Pression: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.println("-----------------------------");
  delay(2000);
}
