// webserver_functions.cpp
#include "webserver_functions.h"
#include "global_variables.h"

void setupWebServer(AsyncWebServer &server, Preferences &preferences,
                    String &modifiedHtmlCode) {
  // Server Root
  server.on("/", HTTP_GET, [modifiedHtmlCode](AsyncWebServerRequest *request) {
    request->send(200, "text/html", modifiedHtmlCode);
  });

  // Set time triggers

  server.on("/settime1", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              String feedingTime = request->arg("feedingTime1");

              if (feedingTime != "") {
                preferences.putString("feedingTime1", feedingTime);
                modifyHtml(preferences);
                lcd.setCursor(0, 2);
                lcd.print(preferences.getString("feedingTime2", "") + " " +
                          preferences.getString("feedingTime3", "") + " " +
                          preferences.getString("feedingTime4", ""));
                lcd.setCursor(15, 1);
                lcd.print(preferences.getString("feedingTime1", ""));
                request->send(200, "text/html",
                              "Feeding time 1 set to " + feedingTime +
                                  modifiedHtmlCode);
              } else {
                request->send(400, "text/html",
                              "No feeding time provided" + modifiedHtmlCode);
              }
            });

  server.on("/settime2", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              String feedingTime = request->arg("feedingTime2");
              if (feedingTime != "") {
                preferences.putString("feedingTime2", feedingTime);
                modifyHtml(preferences);
                lcd.setCursor(0, 2);
                lcd.print(preferences.getString("feedingTime2", "") + " " +
                          preferences.getString("feedingTime3", "") + " " +
                          preferences.getString("feedingTime4", ""));
                lcd.setCursor(15, 1);
                lcd.print(preferences.getString("feedingTime1", ""));
                request->send(200, "text/html",
                              "Feeding time 2 set to " + feedingTime +
                                  modifiedHtmlCode);
              } else {
                request->send(400, "text/html",
                              "No feeding time provided" + modifiedHtmlCode);
              }
            });

  server.on("/settime3", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              String feedingTime = request->arg("feedingTime3");
              if (feedingTime != "") {
                preferences.putString("feedingTime3", feedingTime);
                modifyHtml(preferences);
                lcd.setCursor(0, 2);
                lcd.print(preferences.getString("feedingTime2", "") + " " +
                          preferences.getString("feedingTime3", "") + " " +
                          preferences.getString("feedingTime4", ""));
                lcd.setCursor(15, 1);
                lcd.print(preferences.getString("feedingTime1", ""));
                request->send(200, "text/html",
                              "Feeding time 3 set to " + feedingTime +
                                  modifiedHtmlCode);
              } else {
                request->send(400, "text/html",
                              "No feeding time provided" + modifiedHtmlCode);
              }
            });

  server.on("/settime4", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              String feedingTime = request->arg("feedingTime4");
              if (feedingTime != "") {
                preferences.putString("feedingTime4", feedingTime);
                modifyHtml(preferences);
                lcd.setCursor(0, 2);
                lcd.print(preferences.getString("feedingTime2", "") + " " +
                          preferences.getString("feedingTime3", "") + " " +
                          preferences.getString("feedingTime4", ""));
                lcd.setCursor(15, 1);
                lcd.print(preferences.getString("feedingTime1", ""));

                request->send(200, "text/html",
                              " Feeding time 4 set to " + feedingTime +
                                  modifiedHtmlCode);
              } else {
                request->send(400, "text/html",
                              "No feeding time provided" + modifiedHtmlCode);
              }
            });

  // Clear Feeding Time

  server.on("/cleartime", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              String argValue = request->arg("feedingTime");
              if (argValue.toInt() >= 1 && argValue.toInt() <= 4) {
                preferences.putString("feedingTime", "");
                preferences.remove(("feedingTime" + argValue).c_str());
                modifyHtml(preferences);
                request->send(200, "text/html",
                              "Trigger time " + argValue + " cleared" +
                                  modifiedHtmlCode);
              } else {
                request->send(400, "text/html",
                              "Invalid trigger time" + modifiedHtmlCode);
              }
            });

  // Toggle feeding

  server.on("/feed", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              feedLogic();

              request->send(200, "text/html",
                            "Feeding... Gate opened and closed" +
                                modifiedHtmlCode);
            });  
  
  // Control the Gate Servo Open and close

  server.on("/servo", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              if (request->hasParam("angle", true)) {
                String angleStr = request->getParam("angle", true)->value();
                int angle = angleStr.toInt();
                if (angle == closedAngle || angle == openAngle) {
                  servo.write(angle);
                  String action = (angle == closedAngle) ? "Closed" : "Opened";
                  request->send(200, "text/html",
                                "Gate " + action + " at " + angleStr +
                                    " degrees" + modifiedHtmlCode);
                } else {
                  request->send(400, "text/html",
                                "Invalid angle. Valid angles are " +
                                    String(closedAngle) + " and " +
                                    String(openAngle) + modifiedHtmlCode);
                }
              } else {
                request->send(400, "text/html",
                              "Angle parameter missing" + modifiedHtmlCode);
              }
            });  

  // Control Stepper Carousel

  server.on(
      "/carousel", HTTP_POST,
      [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
        if (request->hasParam("angle", true)) {
          String angleStr = request->getParam("angle", true)->value();
          int angle = angleStr.toInt();

          if (angle == 1 || angle == 2 || angle == 4 || angle == 8) {
            // Move the stepper motor according to the specified angle
            int steps = 2048 / angle; // Assuming 2048 steps for 360 degrees
            stepper.step(steps);

            //                  for (int i = 0; i < steps; i++) {
            //                    stepper.step(1);
            //                    delay(2);
            //                  }
            request->send(200, "text/html",
                          "Carousel rotated by " + String(steps) + " Steps" +
                              modifiedHtmlCode);
          } else {
            request->send(
                400, "text/html",
                "Invalid angle. Valid angles are 45, 90, 180, and 360 degrees" +
                    modifiedHtmlCode);
          }
        } else {
          request->send(400, "text/html",
                        "Angle parameter missing" + modifiedHtmlCode);
        }
      });

  // Set timezone

  server.on("/settimezone", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              int timezone = request->arg("timezone").toInt();
              preferences.putInt("timezone", timezone);

              String ntpServer = request->arg("ntpServer");
              preferences.putString("ntpServer", ntpServer);

              timeClient.setTimeOffset(timezone); // Update NTP client timezone
              timeClient.setPoolServerName(ntpServer.c_str()); // Set NTP server

              request->send(200, "text/html",
                            "Timezone set to GMT " + String(timezone) +
                                " and NTP Server set to " + ntpServer +
                                modifiedHtmlCode);
            });

  // Configure Theme

  server.on("/configtheme", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              String buttonColor = request->arg("buttonColor");
              String bgColor = request->arg("bgColor");
              String textColor = request->arg("textColor");
              String borderColor = request->arg("borderColor");
              // Fetch stored theme preferences from preferences
              String headerBgColor =
                  preferences.getString("headerBgColor", "#333");
              int headerTextSize = preferences.getInt("headerTextSize", 2);
              int buttonTextSize = preferences.getInt("buttonTextSize", 1);
              int borderSize = preferences.getInt("borderSize", 2);
              int borderRadius = preferences.getInt("borderRadius", 25);

              // Store the selected colors in preferences
              preferences.putString("buttonColor", buttonColor);
              preferences.putString("bgColor", bgColor);
              preferences.putString("textColor", textColor);
              preferences.putString("borderColor", borderColor);
              preferences.putString("headerBgColor", headerBgColor);
              preferences.putInt("headerTextSize", headerTextSize);
              preferences.putInt("buttonTextSize", buttonTextSize);
              preferences.putInt("borderSize", borderSize);
              preferences.putInt("borderRadius", borderRadius);
              modifyHtml(preferences); // Update the HTML with new colors
              request->send(200, "text/html",
                            "Theme updated successfully" + modifiedHtmlCode);
            });

  // Saving DHCP Settings

  server.on("/save", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              String ssid = request->arg("ssid");
              String new_password = request->arg("password");

              preferences.putString("ssid", ssid);
              preferences.putString("password", new_password);

              request->send(200, "text/html",
                            "Settings saved. Restarting ESP32...");
              ESP.restart();
            });

  // Set the image

  server.on("/setheaderimage", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              headerImageUrl = request->arg("headerImageUrl");
              preferences.putString("headerImageUrl", headerImageUrl);
              modifyHtml(preferences);
              request->send(200, "text/html",
                            "Header image URL set to: " + headerImageUrl +
                                modifiedHtmlCode);
            });

  // Set stepper step per rotation

  server.on(
      "/setstepper", HTTP_POST,
      [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
        String stepsStr = request->arg("stepsPerRotation");
        if (stepsStr != "") {
          int stepsPerRotation = stepsStr.toInt();
          // Ensure stepsPerRotation is within a valid range
          if (stepsPerRotation > 0) {
            preferences.putInt("stepsPerRotation", stepsPerRotation);
            modifyHtml(preferences);
            request->send(200, "text/html",
                          "Steps per Rotation set to " + stepsStr +
                              modifiedHtmlCode);
          } else {
            request->send(
                400, "text/html",
                "Invalid value for Steps per Rotation. Must be greater than 0" +
                    modifiedHtmlCode);
          }
        } else {
          request->send(400, "text/html",
                        "Steps per Rotation parameter missing" +
                            modifiedHtmlCode);
        }
      });

  // Configure openAngle and CloseAngle for Servo

  server.on(
      "/setangles", HTTP_POST, [&preferences](AsyncWebServerRequest *request) {
        if (request->hasParam("openAngle") &&
            request->hasParam("closedAngle")) {
          int openAngle = request->getParam("openAngle")->value().toInt();
          int closedAngle = request->getParam("closedAngle")->value().toInt();
          preferences.putInt("openAngle", openAngle);
          preferences.putInt("closedAngle", closedAngle);
          request->send(200, "text/plain", "Angles set successfully");
        } else {
          request->send(400, "text/plain", "Invalid parameters");
        }
      });

  // Reboot the Machine

  server.on("/reboot", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              // Send response before rebooting
              request->send(200, "text/html",
                            "Rebooting... Plese Use the link Pavlov Machine in "
                            "the header to reload UI" +
                                modifiedHtmlCode);
              // Delay a short time to allow the response to be sent
              delay(1000);
              // Reboot the ESP32

              ESP.restart();
            });

  // Factory reset clear preferences

  server.on("/factoryreset", HTTP_POST,
            [&preferences, &modifiedHtmlCode](AsyncWebServerRequest *request) {
              // Clear all preferences
              preferences.clear();
              // Send response indicating factory reset
              request->send(200, "text/html",
                            "Factory reset completed. Restarting ESP32...");
              // Delay a short time to allow the response to be sent
              delay(1000);
              // Reboot the ESP32
              ESP.restart();
            });

  server.begin();
}
