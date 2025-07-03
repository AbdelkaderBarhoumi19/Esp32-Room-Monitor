#include <WiFi.h>
#include <FirebaseESP32.h>
#include "DHT.h"

// Wi-Fi credentials
#define WIFI_SSID "................."
#define WIFI_PASSWORD "................"

// Firebase credentials
#define FIREBASE_HOST "........................................"
#define FIREBASE_AUTH "....................................."

// DHT Sensor setup
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// smoke sensor (mq2)
#define smoke_pin 35
// Firebase object
FirebaseData firebaseData;

// Variables
float humidity = 0;
float temperatureC = 0;
int smoke_value = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(smoke_pin, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected.");

  // Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void sensor() {
  // DHT22 readings
  humidity = dht.readHumidity();
  temperatureC = dht.readTemperature();

  if (isnan(humidity) || isnan(temperatureC) ) {
    Serial.println("Failed to read from DHT22 sensor!");
    return;
  }

  // smoke sensor
  int smoke_value = analogRead(smoke_pin);

  // Debug output
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  DHT Temp: ");
  Serial.print(temperatureC);
  Serial.print("°C  Smoke: ");
  Serial.print(smoke_value);

}

void loop() {

  sensor();

  // Send to Firebase
  Firebase.setFloat(firebaseData, "/DHT22/Humidity", humidity);
  Firebase.setFloat(firebaseData, "/DHT22/TemperatureC", temperatureC);
  Firebase.setInt(firebaseData, "/MQ2/Smoke", smoke_value);

  delay(2000);  // 2-second delay between readings
}