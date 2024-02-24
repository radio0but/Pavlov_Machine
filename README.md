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

- ESP32 Dev Kit
- Servo motor MJ90S
- Stepper motor 28BYJ-48 with ULN2003 PCB
- [3D printed parts](https://www.tinkercad.com/things/hWJ3R70zxII-pavlov-machine) 
- An on-off switch
- Power supply 5 volt 3 amp +


## Setup

1. Connect the servo motor to the designated pin on the ESP32.
2. Connect the stepper motor to the designated pins on the ESP32.
3. Configure the WiFi settings in the code to connect to your local network.
4. Upload the code to the ESP32.
5. Access the web interface by navigating to the IP address of the ESP32 in a web browser.

## Usage

1. Set feeding times using the web interface.
2. Control the feeding gate to open and close.
3. Dispense food from the carousel in different increments.
4. Configure WiFi settings and timezone as needed.
5. Set a custom header image for the user interface.
