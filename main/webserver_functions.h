#ifndef WEBSERVER_FUNCTIONS_H
#define WEBSERVER_FUNCTIONS_H

#include <Preferences.h>
#include <ESPAsyncWebServer.h>

void setupWebServer(AsyncWebServer &server, Preferences &preferences, String &modifiedHtmlCode);

#endif
