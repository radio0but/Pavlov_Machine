#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>

extern Preferences preferences;

void connectToWiFi();
void startAPMode();

#endif // WIFI_H
