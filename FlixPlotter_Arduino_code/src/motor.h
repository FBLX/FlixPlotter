#include <Arduino.h>

class Motor
{
    public:
        int stepPin;
        int dirPin;
        int enPin;
        bool invertOrientation;

        volatile unsigned long absStepPosition;
        volatile unsigned long stepsToGo;
        volatile unsigned long stepsDone;
        volatile int stepDirection;
        volatile bool movementFinished;
        volatile unsigned int maxSpeed;
        volatile unsigned int acceleration;
        volatile unsigned int rampUpStepCount;
        volatile unsigned int currDelay;


        Motor(int sP, int dP, int eP, bool inv);

        void step(int dir);
        void setAbsPos(unsigned long aP);

};


class MultiMotor
{
    public:
        Motor leftMotor;
        Motor rightMotor;
};