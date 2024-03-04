#include "global_variables.h"

int prevMinute =
    -1; // Initialize with a value that won't match any valid minute

const char *ap_ssid = "PetFeederGO";
const char *default_ap_password = "password";
const int servoPin = 2;
int closedAngle = 0;
int openAngle = 90;
// Define stepper motor pins
const int STEPPER_PIN1 = 15;
const int STEPPER_PIN2 = 12;
const int STEPPER_PIN3 = 27;
const int STEPPER_PIN4 = 4;

String hourString;

LiquidCrystal_I2C lcd(0x27, 20, 4);
AsyncWebServer server(80);
Preferences preferences;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
Stepper stepper(preferences.getInt("stepsPerRotation", 2048), STEPPER_PIN1,
                STEPPER_PIN2, STEPPER_PIN3, STEPPER_PIN4);
Servo servo;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL); // Attach the I2C pins (SDA and SCL)
  lcd.init();           // LCD driver initialization
  lcd.backlight();      // Turn on the backlight

  headerImageUrl = preferences.getString("headerImageUrl", "");
  servo.attach(servoPin);
  stepper.setSpeed(10); // Set the speed of the stepper motor in RPM
  preferences.begin("wifi", false);

// Wifi connection initialisation
  connectToWiFi();
  
  lcdPrint();

  // Initialize NTP
  timeClient.begin();
  timeClient.setTimeOffset(
      preferences.getInt("timezone", 0)); // Set timezone offset
  timeClient.setUpdateInterval(60000);    // Update time every 60 seconds

  // Fetch stored trigger times from preferences
  modifyHtml(preferences);
  // Set up server with modified HTML code
  setupWebServer(server, preferences,
                 modifiedHtmlCode); // Call the function to set up the server
}



void loop() {
  timeClient.update(); // Update the NTP time
  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();
  currentHour += preferences.getInt("timezone", 0);
  // Normalize current hour to be within 0-23 range
  if (currentHour < 0) {
    currentHour += 24; // If negative, add 24 hours to normalize
  } else if (currentHour >= 24) {
    currentHour -=
        24; // If greater than or equal to 24, subtract 24 hours to normalize
  }

  // Adjust current hour by adding the timezone offset

  hourString = String(currentHour) + ":" + String(currentMinute);

  // Check if the current minute is different from the previous minute
  if (currentMinute != prevMinute) {
    lcdPrint(); // Refresh the LCD only if the minute has changed
    prevMinute = currentMinute; // Update the previous minute value
  }

  for (int i = 1; i <= 3; i++) {
    String feedingTime =
        preferences.getString(("feedingTime" + String(i)).c_str(), "");
    if (feedingTime != "") {

      int feedingHour = feedingTime.substring(0, 2).toInt();
      int feedingMinute = feedingTime.substring(3, 5).toInt();

      if (currentHour == feedingHour && currentMinute == feedingMinute) {

        feedLogic();

        delay(60000);
      }
    }
  }
}
