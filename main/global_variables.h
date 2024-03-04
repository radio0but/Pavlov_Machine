#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <TimeLib.h>
#include <WiFi.h>
#include <Preferences.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Stepper.h>
#include "html_code.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "petfeeder.h"
#include "webserver_functions.h"
#include "LCD.h"
#include "wifi.h"

extern const char *ap_ssid;
extern const char *default_ap_password;
extern const int servoPin;
extern int closedAngle;
extern int openAngle;
extern const int STEPPER_PIN1;
extern const int STEPPER_PIN2;
extern const int STEPPER_PIN3;
extern const int STEPPER_PIN4;
extern String hourString;
extern LiquidCrystal_I2C lcd;
extern AsyncWebServer server;
extern Preferences preferences;
extern WiFiUDP ntpUDP;
extern NTPClient timeClient;
extern Stepper stepper;
extern Servo servo;
extern String modifiedHtmlCode;
#endif
