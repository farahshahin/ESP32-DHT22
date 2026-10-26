# ESP32-DHT22
ESP32 temperature and humidity monitoring using DHT22 and ThingSpeak.
# ESP32 to ThingSpeak: Temperature and Humidity Monitoring

## Project Description
This project uses an ESP32 and a DHT22 sensor to measure temperature and humidity. The readings are sent to ThingSpeak using an HTTP request and displayed on public charts.

## Student Information
- Full Name:Farah Shahin
- University ID: 12324274

## Hardware and Simulation
- ESP32 DevKit
- DHT22 temperature and humidity sensor
- Wokwi simulator

## Wiring
- DHT22 VCC → ESP32 3.3V
- DHT22 GND → ESP32 GND
- DHT22 SDA (DATA) → ESP32 GPIO 15

## ThingSpeak Configuration
- Field 1: Temperature (°C)
- Field 2: Humidity (%)
- Channel Visibility: Public
- Data Upload Interval: 20 seconds

## ThingSpeak Public Channel
https://thingspeak.mathworks.com/channels/3551664

## Wokwi Simulation
https://wokwi.com/projects/478958997586449409
## Source Code
The ESP32 source code is available in `wifi-scan.ino`.

## Screenshots
See the `screenshots` folder for the simulation, ThingSpeak charts, and channel settings.
<img width="476" height="419" alt="image" src="https://github.com/user-attachments/assets/35a0924a-38d9-4de3-a074-b8ad03155a5a" />
<img width="841" height="287" alt="image" src="https://github.com/user-attachments/assets/5aafb21d-72fc-4d4c-8cf8-3cb3c77a2b94" />
<img width="410" height="433" alt="image" src="https://github.com/user-attachments/assets/b892d85a-0d75-44d0-9346-455978e09c06" />



## Security Note
The ThingSpeak Write API Key is kept out of the public repository.
