#ifndef Propulsion_h
#define Propulsion_h

#include "Arduino.h"
#include "MissionHelper.h"

class Propulsion
{
  public:
    Propulsion(MissionHelper mission);
    void driveFwd();
    void driveFwdS(int speed);
    void driveBackwd();
    void driveBackwdS(int speed);
    void stopMotors();
    void sendMotorsLeft();
    void sendMotorsRight();
    void turnTo(float targetTheta);
    float degToRad(int deg);
  private:
    const int HBENA = 10;
    const int HBENB = 11;
    const int HBADir1 = 7;
    const int HBBDir1 = 2;
    const int HBADir2 = 6;
    const int HBBDir2 = 13;
    const int defaultPropSpeed = 100;
    const int turnSpeed = 50;
    const float thetaBuffer = 0.25;
    MissionHelper _mission;
};

#endif
