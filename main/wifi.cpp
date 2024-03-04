#include "global_variables.h"
#include "wifi.h"

void connectToWiFi() {
String ssid = preferences.getString("ssid", "");
String password = preferences.getString("password", default_ap_password);

  if (ssid.length() > 0 && password.length() > 0) {
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.println("Connecting to WiFi...");
    lcd.setCursor(0, 3);
    lcd.print("Connecting to WiFi..");
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 10) {
      delay(1000);
      Serial.print(".");
      retries++;
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("WiFi connected...");
      lcd.setCursor(0, 3);
      lcd.print("WiFi connected      ");
      lcd.setCursor(0, 1);
      lcd.print(WiFi.localIP());
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
      delay(1000);
      lcd.setCursor(0, 3);
      lcd.print("                    ");
    } else {
      Serial.println("Failed to connect to WiFi. Starting Access Point mode.");
      startAPMode();
    }
  } else {
    Serial.println("No WiFi credentials saved. Starting Access Point mode.");
    startAPMode();
  }
}



// Start Access Point Mode

void startAPMode() {
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
