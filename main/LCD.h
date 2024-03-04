#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Preferences.h>
#include <WiFi.h>
#include <NTPClient.h>

extern LiquidCrystal_I2C lcd;
extern Preferences preferences;
extern WiFiUDP ntpUDP;
extern NTPClient timeClient;

void lcdPrint();

#endif // LCD_H
