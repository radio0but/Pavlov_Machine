#include "feeding_logic.h"

void feedLogic() {
    lcd.setCursor(10, 1);
    lcd.print("Feeding..");
    servo.write(openAngle);

    delay(750);

    servo.write(closedAngle);

    delay(250);

    stepper.step(512);
    lcd.setCursor(10, 1);
    lcd.print("          ");
}
