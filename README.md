ESP32 Room Monitor

📡 An ESP32-based system to monitor room conditions, including temperature, humidity, and smoke/gas levels.
📌 Features

    🌡️ Temperature & Humidity (via DHT22 sensor)

    🔥 Smoke/Gas Detection (via MQ2 sensor)

    📊 Serial Monitor Output (Real-time sensor data)

🛠️ Components
Component	Description
ESP32	Main microcontroller
DHT22	High-precision temperature & humidity sensor
MQ2	Smoke/LPG/CO gas detection sensor
Breadboard & Jumper Wires	For connections
🔌 Wiring Guide
Sensor	ESP32 Pin
DHT22 Data	GPIO 4
MQ2 (Analog)	GPIO 34
MQ2 (VCC)	3.3V
MQ2 (GND)	GND

    Note: The MQ2 sensor requires a 5V supply for the heater coil, but its analog output works at 3.3V (ESP32-safe).

## Usage

1. Clone this repository:
   ```bash
   git clone https://github.com/AbdelkaderBarhoumi19/Esp32-Room-Monitor.git
