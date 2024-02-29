# Pavlov Machine

The Pavlov Machine is a project aimed at automating the feeding process for pets using an ESP32 microcontroller. It allows users to set feeding times, control a servo motor to open and close the feeding gate, and control a stepper motor to dispense food from a carousel.

## Features

- Set multiple feeding times throughout the day.
- Control the opening and closing of the feeding gate.
- Dispense food from the carousel in different increments.
- Configure WiFi settings and timezone.
- Put the Photo of your Pet in the User Interface.

## Dependencies

- [TimeLib](https://github.com/PaulStoffregen/Time) - Timekeeping library for Arduino.
- [WiFi](https://www.arduino.cc/en/Reference/WiFi) - WiFi library for ESP32.
- [Preferences](https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences) - Library for saving preferences in ESP32 flash memory.
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) - Asynchronous Web Server library for ESP32.
- [ESP32Servo](https://github.com/jkb-git/ESP32Servo) - Servo library for ESP32.
- [NTPClient](https://github.com/arduino-libraries/NTPClient) - NTP (Network Time Protocol) library for Arduino.
- [WiFiUdp](https://www.arduino.cc/en/Reference/WiFiUDP) - UDP library for WiFi modules.

## Hardware Requirements

- 3D printed parts
- ESP32 Dev Kit V1 Doit
- Servo motor MJ90S
- Stepper motor 28BYJ-48 Modded for BiPolar operation
- L293D H-Bridge Chip
- LCD with integrated I2C 20 x 4
- Lot of dupon cables
- Small Bread Boards
- on-off switch
- Generic female Barrel to Terminal adapter 
- Some M2 screw 
- Power supply 5 volt 3 amp +


The Project is stil under more improvement more instructions on how to put it togeter to come
