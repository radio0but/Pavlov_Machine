#include "global_variables.h"

const char *ap_ssid = "PetFeederGO";
const char *default_ap_password = "password";

// Define stepper motor pins
const int STEPPER_PIN1 = 15;
const int STEPPER_PIN2 = 12;
const int STEPPER_PIN3 = 27;
const int STEPPER_PIN4 = 4;
const int servoPin = 2;
int closedAngle = 0;
int openAngle = 90;
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
  connectToWiFi(); // Call the WiFi connection function
  initializeTime(); // Call the time initialization function
  lcdPrint(); // Call the LCD printing function
  modifyHtml(preferences);
  setupWebServer(server, preferences,
                 modifiedHtmlCode); // Call the function to set up the server
}

void loop() {
  updateTime(); // Call the time update function
}
