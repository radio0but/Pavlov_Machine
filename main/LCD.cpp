#include "LCD.h"

// everything concerning the LCD

void lcdPrint() {
  // Check if WiFi is not in access point mode
  if (WiFi.getMode() != WIFI_AP) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pavlov Machine");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
    String feedTime1 = preferences.getString("feedingTime1", "");
    String feedTime2 = preferences.getString("feedingTime2", "");
    String feedTime3 = preferences.getString("feedingTime3", "");
    String feedTime4 = preferences.getString("feedingTime4", "");

    lcd.setCursor(4, 2);
    lcd.print("1-");
    lcd.setCursor(13, 2);
    lcd.print("2-");
    lcd.setCursor(4, 3);
    lcd.print("3-");
    lcd.setCursor(13, 3);
    lcd.print("4-");

    if (feedTime1 != "") {
      lcd.setCursor(6, 2);
      lcd.print(preferences.getString("feedingTime1", ""));
    }

    if (feedTime2 != "") {
      lcd.setCursor(15, 2);
      lcd.print(preferences.getString("feedingTime2", ""));
    }

    if (feedTime3 != "") {
      lcd.setCursor(6, 3);
      lcd.print(preferences.getString("feedingTime3", ""));
    }

    if (feedTime4 != "") {
      lcd.setCursor(15, 3);
      lcd.print(preferences.getString("feedingTime4", ""));
    }

    // Format hour and minute with leading zeros
    int currentHour1 = timeClient.getHours();

    currentHour1 += preferences.getInt("timezone", 0);
    // Normalize current hour to be within 0-23 range
    if (currentHour1 < 0) {
      currentHour1 += 24; // If negative, add 24 hours to normalize
    } else if (currentHour1 >= 24) {
      currentHour1 -=
          24; // If greater than or equal to 24, subtract 24 hours to normalize
    }
    String formattedHour =
        (currentHour1 < 10 ? "0" : "") + String(currentHour1);
    String formattedMinute = (timeClient.getMinutes() < 10 ? "0" : "") +
                             String(timeClient.getMinutes());
    String timeString = formattedHour + ":" + formattedMinute;

    lcd.setCursor(15, 0);
    lcd.print(timeString);
  } else {
    lcd.setCursor(0, 3);
    lcd.print("Access Point mode  ");
    lcd.setCursor(0, 0);
    lcd.print("SSID: PetFeederGo");
    lcd.setCursor(0, 1);
    lcd.print("Password: password");
    lcd.setCursor(0, 2);
    lcd.print("IP : 192.168.4.1");
  }
}
