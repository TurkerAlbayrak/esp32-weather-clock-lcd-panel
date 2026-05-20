# ESP32 Weather and Clock Panel

A smart desk clock project built with ESP32 and a 16x2 I2C LCD display.  
The device connects to WiFi, synchronizes time using NTP servers, and displays real-time weather information using the OpenWeather API.

---
(Picture is a example for schema)
<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/60132a33-a705-4c40-a796-c2a94a272fd6" />


## Features

- Real-time clock using NTP
- Live weather data from OpenWeather API
- WiFi connectivity
- 16x2 I2C LCD support
- Lightweight and simple design
- Automatic weather updates

---

## Hardware Used

- ESP32
- 16x2 I2C LCD Display
- Micro USB Cable
- WiFi Connection

---

## Wiring

### LCD -> ESP32

| LCD Pin | ESP32 Pin |
|---------|------------|
| GND     | GND        |
| VCC     | 5V         |
| SDA     | GPIO 21    |
| SCL     | GPIO 22    |

---

## Required Libraries

Install these libraries from the Arduino IDE Library Manager:

- WiFi
- HTTPClient
- ArduinoJson
- LiquidCrystal_I2C

---

## OpenWeather API

Create a free API key from:

https://openweathermap.org/api

Then replace this line in the code:

Future Improvements
Weather icons
Humidity display
Multi-page menu system
Alarm support
Auto reconnect WiFi
Better UI animations
