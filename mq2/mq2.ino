// MQ2 Smoke Sensor with ESP32

//const int mq2Pin = 34; // Analog pin for MQ2 output
#define mq2Pin 4 

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("MQ-2 Smoke Sensor Test");
}

void loop() {
  int sensorValue = digitalRead(mq2Pin); 
  Serial.print("sensorvalue: ");
  Serial.print(sensorValue);

  if (!sensorValue) { 
    Serial.println(" => Smoke detected!");
  } else {
    Serial.println(" => Normal air");
  }

  delay(1000); // Wait 1 second
}
