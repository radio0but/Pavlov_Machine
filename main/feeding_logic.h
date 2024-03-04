#ifndef FEEDING_LOGIC_H
#define FEEDING_LOGIC_H


#include "global_variables.h"

extern Servo servo;
extern Stepper stepper;
extern int openAngle;
extern int closedAngle;

void feedLogic();

#endif // FEEDING_LOGIC_H
