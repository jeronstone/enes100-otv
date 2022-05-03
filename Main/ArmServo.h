#ifndef ArmServo_h
#define ArmServo_h

#include "Arduino.h"
#include "Servo.h"

class ArmServo
{
  public:
    ArmServo();
    void begin();
    void end();
    void runServoCCW();
    void runServoCW();
    void stopServoRotation();
    void runArm(bool dir, int time); //1: down | 0: up
  private:
    Servo servo;
    const int armServoPin = 5;
    const int forward = 1200;
    const int backward = 1800;
    const int stopFreq = 1500;
};

#endif
