# 🚨 Smart Helmet for High-Risk Occupations

![Arduino](https://img.shields.io/badge/Platform-Arduino-blue)
![C++](https://img.shields.io/badge/Language-C%2B%2B-red)
![IoT](https://img.shields.io/badge/Category-IoT-orange)

## Overview

The **Smart Helmet** monitors worker safety in real-time. It tracks **heart rate**, **falls**, **temperature & humidity**, and **toxic gas levels**, sending **instant SMS alerts** during emergencies. Ideal for mines, construction sites, and hazardous workplaces.

---

## Features

* ✅ Heart Rate Monitoring (MAX30100)
* ✅ Fall Detection (MPU6050)
* ✅ Temperature & Humidity Monitoring (DHT11)
* ✅ Toxic Gas Detection (MQ135)
* ✅ SMS Alerts with Location (SIM800C)

---

## Components

* **Microcontroller:** Arduino Uno
* **Sensors:** MAX30100, MPU6050, DHT11, MQ135
* **Module:** SIM800C GSM
* **Other:** Breadboard, Jumper Wires, Buzzer, Push Switch, 12V Battery

---

## Wiring Table

| Component  | Arduino Pin    |
| ---------- | -------------- |
| MAX30100   | I2C (SDA, SCL) |
| MPU6050    | I2C (SDA, SCL) |
| DHT11      | Digital 2      |
| MQ135      | Analog A0      |
| SIM800C TX | Pin 11         |
| SIM800C RX | Pin 12         |

---

## Installation

1. Install **Arduino IDE**: [Download](https://www.arduino.cc/en/software)
2. Install required libraries:

   ```cpp
   #include <Wire.h>
   #include "MAX30100_PulseOximeter.h"
   #include <Adafruit_MPU6050.h>
   #include <Adafruit_Sensor.h>
   #include <SoftwareSerial.h>
   #include <DHT.h>
   ```
3. Connect sensors and modules according to the wiring table.
4. Replace `<PHONE NUMBER>` in `sendSMS()` function.
5. (Optional) Replace `<LAT>` & `<LON>` with real-time GPS coordinates.
6. Upload the code to **Arduino Uno**.
7. Open Serial Monitor at **9600 baud** to view readings.

---

## Alerts

* **Heart Rate:** BPM < 50 or > 120 → SMS Alert
* **Fall Detection:** Acceleration > 3.5 m/s² → Emergency SMS
* **Gas Detection:** MQ135 > 600 → Alert SMS

---

## Usage

```cpp
// Example: Sending SMS on fall detection
if(acceleration > FALL_THRESHOLD){
    sendSMS("Fall Detected! Urgent Help Needed! Location: https://maps.google.com/?q=<LAT>,<LON>");
}
```

---

## Notes

* Adjust thresholds according to real-world calibration.
* Ensure SIM800C has an active SIM card.
* Delay added after SMS to prevent spamming.

---

## Author

**Sri Yazhini**
Final Year Engineering Student


