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



#define SDA 21  // Define SDA pins
#define SCL 22  // Define SCL pins

/*
 * note: If lcd2004 uses PCF8574T, IIC's address is 0x27,
 *       or lcd2004 uses PCF8574AT, IIC's address is 0x3F.
*/
LiquidCrystal_I2C lcd(0x27,20,4); 

AsyncWebServer server(80);

Preferences preferences;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

const char *ap_ssid = "PetFeederGO";
const char *default_ap_password = "password";
const int servoPin = 2;
const int closedAngle = 0;
const int openAngle = 90;
// Define stepper motor pins
const int STEPPER_PIN1 = 15;
const int STEPPER_PIN2 = 12;
const int STEPPER_PIN3 = 27;
const int STEPPER_PIN4 = 4;

String hourString;


Stepper stepper(preferences.getInt("stepsPerRotation", 2048), STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4); // Declare the Stepper object

Servo servo;

void setup()
{  
  Serial.begin(115200);
  Wire.begin(SDA, SCL); // Attach the I2C pins (SDA and SCL)
  lcd.init();           // LCD driver initialization
  lcd.backlight();      // Turn on the backlight

  
 
  headerImageUrl = preferences.getString("headerImageUrl", "");
  servo.attach(servoPin);
  stepper.setSpeed(10); // Set the speed of the stepper motor in RPM
  preferences.begin("wifi", false);

  String ssid = preferences.getString("ssid", "");
  String password = preferences.getString("password", default_ap_password);

  if (ssid.length() > 0 && password.length() > 0)
  {
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.println("Connecting to WiFi...");
    lcd.setCursor(0, 3);  
    lcd.print("Connecting to WiFi..");
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 10)
    {
      delay(1000);
      Serial.print(".");
      retries++;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("WiFi connected...");
       lcd.setCursor(0, 3);  
    lcd.print("WiFi connected      ");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
    }
    else
    {
      Serial.println("Failed to connect to WiFi. Starting Access Point mode.");
      startAPMode();
    }
  }
  else
  {
    Serial.println("No WiFi credentials saved. Starting Access Point mode.");
    startAPMode();
  }
  lcdPrint();

  // Initialize NTP
  timeClient.begin();
  timeClient.setTimeOffset(preferences.getInt("timezone", 0)); // Set timezone offset
  timeClient.setUpdateInterval(60000); // Update time every 60 seconds

 
  // Fetch stored trigger times from preferences
  modifyHtml(preferences);
  // Set up server with modified HTML code
  server.on("/", HTTP_GET, [modifiedHtmlCode](AsyncWebServerRequest *request) {
    request->send(200, "text/html", modifiedHtmlCode);
  });

  server.on("/save", HTTP_POST, [](AsyncWebServerRequest *request)
            {
              String ssid = request->arg("ssid");
              String new_password = request->arg("password");

              preferences.putString("ssid", ssid);
              preferences.putString("password", new_password);

              request->send(200, "text/html", "Settings saved. Restarting ESP32...");
              ESP.restart();
            });


server.on("/reboot", HTTP_POST, [](AsyncWebServerRequest *request) {
  // Send response before rebooting
  request->send(200, "text/html", "Rebooting... Plese Use the link Pavlov Machine in the header to reload UI" + modifiedHtmlCode);
  // Delay a short time to allow the response to be sent
  delay(1000);
  // Reboot the ESP32

  ESP.restart();
});
 server.on("/setheaderimage", HTTP_POST, [](AsyncWebServerRequest *request) {
    headerImageUrl = request->arg("headerImageUrl");
    preferences.putString("headerImageUrl", headerImageUrl);
    modifyHtml(preferences);
    request->send(200, "text/html", "Header image URL set to: " + headerImageUrl + modifiedHtmlCode);
});
           
server.on("/settime1", HTTP_POST, [](AsyncWebServerRequest *request) {
    String feedingTime = request->arg("feedingTime1");
 
    if (feedingTime != "") {
      preferences.putString("feedingTime1", feedingTime);
      modifyHtml(preferences);
      lcd.setCursor(0, 2); 
       lcd.print(preferences.getString("feedingTime2", "") + " " + preferences.getString("feedingTime3", "") + " " + preferences.getString("feedingTime4", ""));
        lcd.setCursor(15, 1); 
       lcd.print(preferences.getString("feedingTime1", ""));
      request->send(200, "text/html", "Feeding time 1 set to " + feedingTime + modifiedHtmlCode);
    } else {
      request->send(400, "text/html", "No feeding time provided" + modifiedHtmlCode);
    }
});

server.on("/settime2", HTTP_POST, [](AsyncWebServerRequest *request) {
    String feedingTime = request->arg("feedingTime2");
    if (feedingTime != "") {
      preferences.putString("feedingTime2", feedingTime);
      modifyHtml(preferences);
      lcd.setCursor(0, 2); 
       lcd.print(preferences.getString("feedingTime2", "") + " " + preferences.getString("feedingTime3", "") + " " + preferences.getString("feedingTime4", ""));
        lcd.setCursor(15, 1); 
       lcd.print(preferences.getString("feedingTime1", ""));
      request->send(200, "text/html", "Feeding time 2 set to " + feedingTime + modifiedHtmlCode);
    } else {
      request->send(400, "text/html", "No feeding time provided" + modifiedHtmlCode);
    }
});

server.on("/settime3", HTTP_POST, [](AsyncWebServerRequest *request) {
    String feedingTime = request->arg("feedingTime3");
    if (feedingTime != "") {
      preferences.putString("feedingTime3", feedingTime);
      modifyHtml(preferences);
      lcd.setCursor(0, 2); 
       lcd.print(preferences.getString("feedingTime2", "") + " " + preferences.getString("feedingTime3", "") + " " + preferences.getString("feedingTime4", ""));
        lcd.setCursor(15, 1); 
       lcd.print(preferences.getString("feedingTime1", ""));
      request->send(200, "text/html", "Feeding time 3 set to " + feedingTime + modifiedHtmlCode);
    } else {
      request->send(400, "text/html", "No feeding time provided" + modifiedHtmlCode);
    }
});

server.on("/settime4", HTTP_POST, [](AsyncWebServerRequest *request) {
    String feedingTime = request->arg("feedingTime4");
    if (feedingTime != "") {
      preferences.putString("feedingTime4", feedingTime);
      modifyHtml(preferences);
      lcd.setCursor(0, 2); 
       lcd.print(preferences.getString("feedingTime2", "") + " " + preferences.getString("feedingTime3", "") + " " + preferences.getString("feedingTime4", ""));
        lcd.setCursor(15, 1); 
       lcd.print(preferences.getString("feedingTime1", ""));

      request->send(200, "text/html", " Feeding time 4 set to " + feedingTime +  modifiedHtmlCode);
    } else {
      request->send(400, "text/html", "No feeding time provided" + modifiedHtmlCode);
    }
});


server.on("/carousel", HTTP_POST, [](AsyncWebServerRequest *request)
            {
              if (request->hasParam("angle", true))
              {
                String angleStr = request->getParam("angle", true)->value();
                int angle = angleStr.toInt();
             
                if (angle == 1 || angle == 2 || angle == 4 || angle == 8)
                {
                  // Move the stepper motor according to the specified angle
                  int steps = 2048 / angle; // Assuming 2048 steps for 360 degrees
                    stepper.step(steps);
                    
//                  for (int i = 0; i < steps; i++) {
//                    stepper.step(1);
//                    delay(2);
//                  }
                  request->send(200, "text/html", "Carousel rotated by " + String(steps) + " Steps" + modifiedHtmlCode);
                }
                else
                {
                  request->send(400, "text/html", "Invalid angle. Valid angles are 45, 90, 180, and 360 degrees" + modifiedHtmlCode);
                }
              }
              else
              {
                request->send(400, "text/html", "Angle parameter missing" + modifiedHtmlCode);
              }
            });



  server.on("/cleartime", HTTP_POST, [](AsyncWebServerRequest *request) {
    String argValue = request->arg("feedingTime");
    if (argValue.toInt() >= 1 && argValue.toInt() <= 4) {
      preferences.putString("feedingTime", "");
      preferences.remove(("feedingTime" + argValue).c_str());
      modifyHtml(preferences);
      request->send(200, "text/html", "Trigger time " + argValue + " cleared" + modifiedHtmlCode);
    } else {
      request->send(400, "text/html", "Invalid trigger time" + modifiedHtmlCode);
    }
  });
  server.on("/settimezone", HTTP_POST, [](AsyncWebServerRequest *request)
            {
              int timezone = request->arg("timezone").toInt();
              preferences.putInt("timezone", timezone);

              String ntpServer = request->arg("ntpServer");
              preferences.putString("ntpServer", ntpServer);

              timeClient.setTimeOffset(timezone); // Update NTP client timezone
              timeClient.setPoolServerName(ntpServer.c_str()); // Set NTP server

              request->send(200, "text/html", "Timezone set to GMT " + String(timezone) +
                                               " and NTP Server set to " + ntpServer + modifiedHtmlCode);
            });
server.on("/configtheme", HTTP_POST, [](AsyncWebServerRequest *request) {
    String buttonColor = request->arg("buttonColor");
    String bgColor = request->arg("bgColor");
    String textColor = request->arg("textColor");
    String borderColor = request->arg("borderColor");
    // Fetch stored theme preferences from preferences
    String headerBgColor = preferences.getString("headerBgColor", "#333");
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
    request->send(200, "text/html", "Theme updated successfully" + modifiedHtmlCode);
});

      server.on("/setstepper", HTTP_POST, [](AsyncWebServerRequest *request) {
        String stepsStr = request->arg("stepsPerRotation");
        if (stepsStr != "") {
            int stepsPerRotation = stepsStr.toInt();
            // Ensure stepsPerRotation is within a valid range
            if (stepsPerRotation > 0) {
                preferences.putInt("stepsPerRotation", stepsPerRotation);
                modifyHtml(preferences);
                request->send(200, "text/html", "Steps per Rotation set to " + stepsStr + modifiedHtmlCode);
            } else {
                request->send(400, "text/html", "Invalid value for Steps per Rotation. Must be greater than 0" + modifiedHtmlCode);
            }
        } else {
            request->send(400, "text/html", "Steps per Rotation parameter missing" + modifiedHtmlCode);
        }
    });


  server.on("/feed", HTTP_POST, [](AsyncWebServerRequest *request)
            {
              
              
              feedLogic();
              
              request->send(200, "text/html", "Feeding... Gate opened and closed" + modifiedHtmlCode);
            });

  server.on("/servo", HTTP_POST, [](AsyncWebServerRequest *request)
            {
              if (request->hasParam("angle", true))
              {
                String angleStr = request->getParam("angle", true)->value();
                int angle = angleStr.toInt();
                if (angle == closedAngle || angle == openAngle)
                {
                  servo.write(angle);
                  String action = (angle == closedAngle) ? "Closed" : "Opened";
                  request->send(200, "text/html", "Gate " + action + " at " + angleStr + " degrees" + modifiedHtmlCode);
                }
                else
                {
                  request->send(400, "text/html", "Invalid angle. Valid angles are 0 and 90" + modifiedHtmlCode);
                }
              }
              else
              {
                request->send(400, "text/html", "Angle parameter missing" + modifiedHtmlCode);
              }
            });

  server.begin();
}
void lcdPrint()
{
  // Check if WiFi is not in access point mode
  if (WiFi.getMode() != WIFI_AP) {
    lcd.setCursor(0, 0);  
    lcd.print("Pavlov Machine     ");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
    lcd.setCursor(0, 2); 
    lcd.print(preferences.getString("feedingTime1", "") + " " + preferences.getString("feedingTime2", ""));
    lcd.setCursor(0, 3); 
    lcd.print(preferences.getString("feedingTime3", "") + " " + preferences.getString("feedingTime4", "") + "   ");
    lcd.setCursor(15, 3);  
    lcd.print(hourString);
  }
}
void loop() {
  timeClient.update(); // Update the NTP time
  lcd.setCursor(0, 2); 
  lcd.print(preferences.getString("feedingTime1", "") + " " + preferences.getString("feedingTime2", ""));
  lcd.setCursor(0, 3); 
  lcd.print(preferences.getString("feedingTime3", "") + " " + preferences.getString("feedingTime4", "") + "   ");
  for (int i = 1; i <= 3; i++) {
    String feedingTime = preferences.getString(("feedingTime" + String(i)).c_str(), "");
    if (feedingTime != "") {
      int currentHour = timeClient.getHours();
      int currentMinute = timeClient.getMinutes();
 
      // Adjust current hour by adding the timezone offset
      currentHour += preferences.getInt("timezone", 0);

      // Normalize current hour to be within 0-23 range
      if (currentHour < 0) {
        currentHour += 24; // If negative, add 24 hours to normalize
      } else if (currentHour >= 24) {
        currentHour -= 24; // If greater than or equal to 24, subtract 24 hours to normalize
      }
      hourString = String(currentHour) + ":" + String(currentMinute);
      

      int feedingHour = feedingTime.substring(0, 2).toInt();
      int feedingMinute = feedingTime.substring(3, 5).toInt();
      lcdPrint();
      if (currentHour == feedingHour && currentMinute == feedingMinute) {
     
        feedLogic();

        
        delay(60000);
      }
    }
  }
}

void feedLogic()
{
  
  lcd.setCursor(0, 0);  
  lcd.print("Feeding...         ");
  servo.write(openAngle);
 
  delay(750);

  servo.write(closedAngle);
   
  delay(250);
 
  stepper.step(512);
  lcdPrint();

}// Change the number of steps as needed

void startAPMode()
{
  preferences.putString("password", default_ap_password);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, default_ap_password);
  Serial.println("Access Point mode started.");
  lcd.setCursor(0, 3);  
  lcd.print("Access Point mode  ");
  Serial.print("SSID: ");
  Serial.println(ap_ssid);
  lcd.setCursor(0, 0);  
  lcd.print("SSID: " + String(ap_ssid));
  Serial.print("Password: ");
  Serial.println(default_ap_password);
  lcd.setCursor(0, 1);  
  lcd.print("Password: " + String(default_ap_password));
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  lcd.setCursor(0, 1);  
  lcd.print("IP : " + WiFi.softAPIP());
}
