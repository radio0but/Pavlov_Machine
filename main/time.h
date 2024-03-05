#ifndef TIME_H
#define TIME_H

#include <Arduino.h>
#include <Preferences.h>
#include <NTPClient.h>
#include "global_variables.h"

extern Preferences preferences;
extern NTPClient timeClient;

void initializeTime();

void updateTime();

#endif // TIME_H
