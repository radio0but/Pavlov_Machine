#include "time.h"
int prevMinute =
    -1; // Initialize with a value that won't match any valid minute
void initializeTime() {
    // Initialize NTP
    timeClient.begin();
    timeClient.setTimeOffset(
        preferences.getInt("timezone", 0)); // Set timezone offset
    timeClient.setUpdateInterval(60000);    // Update time every 60 seconds
}

void updateTime() {
    timeClient.update(); // Update the NTP time
    int currentHour = timeClient.getHours();
    int currentMinute = timeClient.getMinutes();
    currentHour += preferences.getInt("timezone", 0);
    // Normalize current hour to be within 0-23 range
    if (currentHour < 0) {
        currentHour += 24; // If negative, add 24 hours to normalize
    } else if (currentHour >= 24) {
        currentHour -= 24; // If greater than or equal to 24, subtract 24 hours to normalize
    }

    // Adjust current hour by adding the timezone offset

    hourString = String(currentHour) + ":" + String(currentMinute);

    // Check if the current minute is different from the previous minute
    if (currentMinute != prevMinute) {
        lcdPrint(); // Refresh the LCD only if the minute has changed
        prevMinute = currentMinute; // Update the previous minute value
    }

    for (int i = 1; i <= 3; i++) {
        String feedingTime = preferences.getString(("feedingTime" + String(i)).c_str(), "");
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
