| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C5 | ESP32-C6 | ESP32-H2 | ESP32-P4 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- | -------- | -------- |

# ESP32 Ultrasonic Smart Blink

This project is an **ESP32-based control system** that uses an **HC-SR04 ultrasonic sensor** to detect the distance of an object and dynamically control the blink rate of an LED. The closer the object is to the sensor, the faster the LED blinks.

## Features
* **Real-time Distance Measurement:** Accurate object detection using the HC-SR04 sensor.
* **Smart Blink Control:** The LED blink frequency is mapped directly to the distance measured (proportional control).
* **Efficient ESP-IDF Framework:** Developed using the Espressif IDE for high-performance firmware management.

## Wiring Schematic
| Component | Pin | ESP32 Pin | Note |
| :--- | :--- | :--- | :--- |
| HC-SR04 | VCC | 5V / VIN | 5V Power Supply |
| HC-SR04 | GND | GND | Common Ground |
| HC-SR04 | Trig | GPIO 5 | Output |
| HC-SR04 | Echo | GPIO 18 | Input (via Voltage Divider) |
| LED | Anode (+) | GPIO 2 | Output |
| LED | Cathode (-) | GND | Ground |

> **Important:** Always use a **Voltage Divider** (1k $\Omega$ and 2k $\Omega$ resistors) on the Echo pin to step down the 5V signal to 3.3V, ensuring the safety of your ESP32 GPIO pin.



[Image of voltage divider circuit diagram]


## How It Works
1. The ESP32 sends a trigger signal and measures the pulse width of the reflected ultrasonic wave via the echo pin.
2. The distance is calculated in centimeters.
3. The result is used to dynamically adjust the blink interval of the LED:
   - **Far object:** Longer delay (slower blink).
   - **Near object:** Shorter delay (faster blink).

## Getting Started
1. Ensure your ESP-IDF environment is properly configured.
2. Clone this repository:
   ```bash
   git clone https://github.com/hafidzsyifa77-lab/ultasonic_sensor_HC-SR04_project
