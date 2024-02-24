#include <TimeLib.h>
#include <WiFi.h>
#include <Preferences.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Stepper.h>

AsyncWebServer server(80);

Preferences preferences;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String headerImageUrl = preferences.getString("headerImageUrl", "");
const char *ap_ssid = "PetFeederGO";
const char *default_ap_password = "password";
String htmlCode;
          
          




                  

const int servoPin = 2;
const int closedAngle = 0;
const int openAngle = 90;
// Define stepper motor pins
const int STEPPER_PIN1 = 14;
const int STEPPER_PIN2 = 12;
const int STEPPER_PIN3 = 13;
const int STEPPER_PIN4 = 4;

String feedingTime1, feedingTime2, feedingTime3, feedingTime4;
String modifiedHtmlCode;

Stepper stepper(2048, STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4); // Declare the Stepper object

Servo servo;

void setup()
{  
  Serial.begin(115200);
            htmlCode += "<html><head><style>"
                  "body { font-family: Tahoma, sans-serif; background-color: black; color: white; display: flex; flex-direction: column; align-items: center; } "
                  ".header { padding: 10px; text-align: center; background-color: #333; color: white; width: 80%;font-size: 2vw; border: 2px solid #73AD21; border-radius: 25px;  } "
                  ".header a {color:white;}" 
                  ".content { display: flex; flex-wrap: wrap; justify-content: space-between; width: 100%; padding: 20px; font-size: 1vw; } "
                  ".column { flex: 1; padding: 20px; width: 90%;border: 2px solid #73AD21; border-radius: 25px;  }"
                  ".column h2 { color: #ddd; }"
                  ".column form { margin-bottom: 20px; }"
                  "input[type='text'], input[type='password'], input[type='submit'], select { padding: 10px; margin: 5px; border: 1px solid #ccc; border-radius: 5px; } "
                  "input[type='submit'] { background-color: #f95300; width: 100%; color: white; cursor: pointer; font-size: 1vw;border: 2px solid #73AD21; border-radius: 25px; } "
                  "input[type='submit']:hover { width: 100%; background-color: #6d2400;font-size: 1.5vw; border: 2px solid #73AD21; border-radius: 25px; } "
                  "input[type='time']{ background-color: #f95300; width: 100%; color: white; cursor: pointer; font-size: 1vw;}"
                  "@media screen and (max-width: 1024px) { .content { flex-direction: column; font-size: 3vw;} .column { width: 100%; } input[type='submit'] {   font-size: 3vw;  } "
                  " input[type='submit']:hover {    font-size: 3.5vw;} input[type='time']{ background-color: #000;  color: white; cursor: pointer; font-size: 6vw;} }"
                  
                  "</style></head>"
                  "<body>"
                  "<div class='header'>"
              "<a href='/' >"
                 "<h1>Pavlov Machine</h1>"
                  "</a>"
                  "</div>"
                  "<div class='content'>"
                  "<div class='column'>"
                  "<h2>Set Feeding Time</h2>"
                  "<form action='/settime1' method='post'>"
                  "Trigger Time 1: <input type='time' name='feedingTime1'>"
                  "<input type='submit' value='Set'>"
                  "</form>"
                  "<form action='/cleartime' method='post'>"
                  "<input type='hidden' name='feedingTime' value='1'>"
                  "<input type='submit' value='Clear Trigger Time 1'>"
                  "</form>"
                  "<form action='/settime2' method='post'>"
                  "Trigger Time 2: <input type='time' name='feedingTime2'>"
                  "<input type='submit' value='Set'>"
                  "</form>"
                  "<form action='/cleartime' method='post'>"
                  "<input type='hidden' name='feedingTime' value='2'>"
                  "<input type='submit' value='Clear Trigger Time 2'>"
                  "</form>"
                  "<form action='/settime3' method='post'>"
                  "Trigger Time 3: <input type='time' name='feedingTime3'>"
                  "<input type='submit' value='Set'>"
                  "</form>"
                  "<form action='/cleartime' method='post'>"
                  "<input type='hidden' name='feedingTime' value='3'>"
                  "<input type='submit' value='Clear Trigger Time 3'>"
                  "</form>"
                  "<form action='/settime4' method='post'>"
                  "Trigger Time 4: <input type='time' name='feedingTime4'>"
                  "<input type='submit' value='Set'>"
                  "</form>"
                  "<form action='/cleartime' method='post'>"
                  "<input type='hidden' name='feedingTime' value='4'>"
                  "<input type='submit' value='Clear Trigger Time 4'>"
                  "</form>"
                  "</div>"
                  "<div class='column'>"
                  "<h2>Feed</h2>"
                  "<form action='/feed' method='post'>"
                  "<input type='submit' value='Feed'>"
                  "</form>"
                  "<h2>Gate controls</h2>"
                  "<form action='/servo' method='post'>"
                  "<input type='hidden' name='angle' value='0'>"
                  "<input type='submit' value='Close Gate'>"
                  "</form>"
                  "<form action='/servo' method='post'>"
                  "<input type='hidden' name='angle' value='90'>"
                  "<input type='submit' value='Open Gate'>"
                  "</form>"
                  "<h2>Carousel Control</h2>"
                  "<form action='/carousel' method='post'>"
                  "<input type='hidden' name='angle' value='8'>"
                  "<input type='submit' value='1/8 Turn'>"
                  "</form>"
                  "<form action='/carousel' method='post'>"
                  "<input type='hidden' name='angle' value='4'>"
                  "<input type='submit' value='1/4 Turn'>"
                  "</form>"
                  "<form action='/carousel' method='post'>"
                  "<input type='hidden' name='angle' value='2'>"
                  "<input type='submit' value='1/2 Turn'>"
                  "</form>"
                  "<form action='/carousel' method='post'>"
                  "<input type='hidden' name='angle' value='1'>"
                  "<input type='submit' value='1 Turn'>"
                  "</form>"
                  "</div>"
                  "<div class='column'>"
                  "<h2>Configurations</h2>"
                    
                  
                  "<h3>Configure your WiFi settings.</h3>"
                  "<form action='/save' method='post'>"
                  "SSID    : <input type='text' name='ssid'><br>"
                  "Password: <input type='password' name='password'><br>"
                  "<input type='submit' value='Save'>"
                  "</form><br>"
                  "<h3>Time Configurations</h3>"
                  "<form action='/settimezone' method='post'>"
                 "Select Timezone: <select name='timezone'>"
                  "<option value='-12'>GMT -12:00</option>"
                  "<option value='-11'>GMT -11:00</option>"
                  "<option value='-10'>GMT -10:00</option>"
                  "<option value='-9'>GMT -9:00</option>"
                  "<option value='-8'>GMT -8:00</option>"
                  "<option value='-7'>GMT -7:00</option>"
                  "<option value='-6'>GMT -6:00</option>"
                  "<option value='-5'>GMT -5:00</option>"
                  "<option value='-4'>GMT -4:00</option>"
                  "<option value='-3'>GMT -3:00</option>"
                  "<option value='-2'>GMT -2:00</option>"
                  "<option value='-1'>GMT -1:00</option>"
                  "<option value='0'>GMT +0:00</option>"
                  "<option value='1'>GMT +1:00</option>"
                  "<option value='2'>GMT +2:00</option>"
                  "<option value='3'>GMT +3:00</option>"
                  "<option value='4'>GMT +4:00</option>"
                  "<option value='5'>GMT +5:00</option>"
                  "<option value='6'>GMT +6:00</option>"
                  "<option value='7'>GMT +7:00</option>"
                  "<option value='8'>GMT +8:00</option>"
                  "<option value='9'>GMT +9:00</option>"
                  "<option value='10'>GMT +10:00</option>"
                  "<option value='11'>GMT +11:00</option>"
                  "<option value='12'>GMT +12:00</option>"
                  "<!-- Add more timezone options here -->"
                  "</select>"
                  "<br> Select NTP Server: <select name='ntpServer'>"
                  "<option value='pool.ntp.org'>pool.ntp.org</option>"
                  "<option value='time.google.com'>time.google.com</option>"
                  "<option value='time.windows.com'>time.windows.com</option>"
                  "<option value='time.apple.com'>time.apple.com</option>"
                  "<option value='time.nist.gov'>time.nist.gov</option>"
                  "<option value='time.cloudflare.com'>time.cloudflare.com</option>"
                  "<!-- Add more NTP server options here -->"
                  "</select>"

                  "<input type='submit' value='Set Timezone and NTP Server'>"
                  "</form>"
                  "<h2>System</h2>" 
                          "<form action='/reboot' method='post'>" 
                          "<input type='submit' value='Reboot'>" 
                          "</form>" 
                  "<h3>Header Image Settings</h3>"
                  "<form action='/setheaderimage' method='post'>"
                  "Header Image URL: <input type='text' name='headerImageUrl'><br>"
                  "<input type='submit' value='Set Header Image'>"
                  "</form>"
                  "</div>"
                  "</div>"
                  "</body></html>";
  servo.attach(servoPin);
  stepper.setSpeed(5); // Set the speed of the stepper motor in RPM
  preferences.begin("wifi", false);

  String ssid = preferences.getString("ssid", "");
  String password = preferences.getString("password", default_ap_password);

  if (ssid.length() > 0 && password.length() > 0)
  {
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.println("Connecting to WiFi...");
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 10)
    {
      delay(1000);
      Serial.print(".");
      retries++;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("WiFi connected");
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

  // Initialize NTP
  timeClient.begin();
  timeClient.setTimeOffset(preferences.getInt("timezone", 0)); // Set timezone offset
  timeClient.setUpdateInterval(60000); // Update time every 60 seconds

 
  // Fetch stored trigger times from preferences
  modifyHtml();
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
    String headerImageUrl = request->arg("headerImageUrl");
    preferences.putString("headerImageUrl", headerImageUrl);
    modifyHtml();
    request->send(200, "text/html", "Header image URL set to: " + headerImageUrl + modifiedHtmlCode);
});
           
server.on("/settime1", HTTP_POST, [](AsyncWebServerRequest *request) {
    String feedingTime = request->arg("feedingTime1");
 
    if (feedingTime != "") {
      preferences.putString("feedingTime1", feedingTime);
      modifyHtml();
      request->send(200, "text/html", "Feeding time 1 set to " + feedingTime + modifiedHtmlCode);
    } else {
      request->send(400, "text/html", "No feeding time provided" + modifiedHtmlCode);
    }
});

server.on("/settime2", HTTP_POST, [](AsyncWebServerRequest *request) {
    String feedingTime = request->arg("feedingTime2");
    if (feedingTime != "") {
      preferences.putString("feedingTime2", feedingTime);
      modifyHtml();
      request->send(200, "text/html", "Feeding time 2 set to " + feedingTime + modifiedHtmlCode);
    } else {
      request->send(400, "text/html", "No feeding time provided" + modifiedHtmlCode);
    }
});

server.on("/settime3", HTTP_POST, [](AsyncWebServerRequest *request) {
    String feedingTime = request->arg("feedingTime3");
    if (feedingTime != "") {
      preferences.putString("feedingTime3", feedingTime);
      modifyHtml();
      request->send(200, "text/html", "Feeding time 3 set to " + feedingTime + modifiedHtmlCode);
    } else {
      request->send(400, "text/html", "No feeding time provided" + modifiedHtmlCode);
    }
});

server.on("/settime4", HTTP_POST, [](AsyncWebServerRequest *request) {
    String feedingTime = request->arg("feedingTime4");
    if (feedingTime != "") {
      preferences.putString("feedingTime4", feedingTime);
      modifyHtml();
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
      modifyHtml();
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
                                               " and NTP Server set to " + ntpServer + htmlCode);
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
void loop() {
  timeClient.update(); // Update the NTP time

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

      int feedingHour = feedingTime.substring(0, 2).toInt();
      int feedingMinute = feedingTime.substring(3, 5).toInt();

      if (currentHour == feedingHour && currentMinute == feedingMinute) {
        feedLogic();
        delay(60000);
      }
    }
  }
}
void modifyHtml()
{
    // Fetch stored trigger times from preferences
    feedingTime1 = preferences.getString("feedingTime1", "");
    feedingTime2 = preferences.getString("feedingTime2", "");
    feedingTime3 = preferences.getString("feedingTime3", "");
    feedingTime4 = preferences.getString("feedingTime4", "");
    headerImageUrl = preferences.getString("headerImageUrl", "");

    // Inject the stored trigger times into the HTML string
    modifiedHtmlCode = htmlCode;
    modifiedHtmlCode.replace("name='feedingTime1'>", "name='feedingTime1' value='" + feedingTime1 + "'>");
    modifiedHtmlCode.replace("name='feedingTime2'>", "name='feedingTime2' value='" + feedingTime2 + "'>");
    modifiedHtmlCode.replace("name='feedingTime3'>", "name='feedingTime3' value='" + feedingTime3 + "'>");
    modifiedHtmlCode.replace("name='feedingTime4'>", "name='feedingTime4' value='" + feedingTime4 + "'>");

    // Inject the stored header image URL into the HTML string
    modifiedHtmlCode.replace("<a href='/' >", "<a href='/' >");
    if (headerImageUrl != "") {
        modifiedHtmlCode.replace("<h2>Set Feeding Time</h2>", "<img src='" + headerImageUrl + "' alt='Header Image' style='width:100%;'></div><div class='column'><h2>Set Feeding Time</h2>");
    } else {
        modifiedHtmlCode.replace("<h2>Set Feeding Time</h2>","<h2>Set Feeding Time</h2>");
    }
}

void feedLogic()
{
  servo.write(openAngle);
  delay(750);
  servo.write(closedAngle);
  delay(250);
  stepper.step(512);
   // Move the stepper motor in half-step increments
 // Move the stepper motor in microstep increments
  // Adjust the number of microsteps and delay as needed
//  for (int i = 0; i < 480 * 8; i++) { // 8 microsteps per full step
//    stepper.step(1); // Microstep forward
//    delayMicroseconds(100); // Adjust delay as needed for your motor and microstepping resolution
//  }
}// Change the number of steps as needed

void startAPMode()
{
  preferences.putString("password", default_ap_password);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, default_ap_password);
  Serial.println("Access Point mode started.");
  Serial.print("SSID: ");
  Serial.println(ap_ssid);
  Serial.print("Password: ");
  Serial.println(default_ap_password);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}
