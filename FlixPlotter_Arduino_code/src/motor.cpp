#include "motor.h"


Motor::Motor(int sP, int dP, int eP, bool inv)
{
    stepPin = sP;
    dirPin = dP;
    enPin = eP;
    invertOrientation = inv;

    absStepPosition = 0;

    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(enPin, OUTPUT);
}

void Motor::step(int dir)
{
    if (invertOrientation)
    {
        dir = dir*-1;
    }
    if (dir == 1)
    {
        digitalWrite(dirPin, HIGH);
    }
    if (dir == -1)
    {
        digitalWrite(dirPin, LOW);
    }
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);

    stepsDone++;
    absStepPosition += dir;
}

void Motor::setAbsPos(unsigned long aP)
{
    absStepPosition = aP;
}