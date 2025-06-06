# ESP32 Room Monitor

This project uses an ESP32 microcontroller to monitor **room conditions** including:

- Temperature & Humidity with **DHT11** sensor
- Atmospheric Pressure & Temperature with **BMP280** sensor

Data is read and printed via the Serial Monitor.

---

## Components

- ESP32 Development Board
- DHT11 Temperature & Humidity Sensor
- BMP280 Pressure Sensor (I2C)
- Connecting wires

---

## Wiring

| Sensor | ESP32 Pin |
|--------|-----------|
| DHT11 Data | GPIO 4 |
| BMP280 SDA | GPIO 21 |
| BMP280 SCL | GPIO 22 |
| Power & Ground | 3.3V & GND |

---

## Usage

1. Clone this repository:
   ```bash
   git clone https://github.com/AbdelkaderBarhoumi19/Esp32-Room-Monitor.git
