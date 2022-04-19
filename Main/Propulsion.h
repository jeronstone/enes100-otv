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
    void turnTo(int theta);
    void turnRALeft();
    void turnLeft(int theta);
    void turnRARight();
    void turnRight(int theta);
    void turnAround();
    void turn90NoVS(bool dir); //1 -> left | 0 -> right
  private:
    const int HBENA = 10;
    const int HBENB = 11;
    const int HBADir1 = 7;
    const int HBBDir1 = 2;
    const int HBADir2 = 6;
    const int HBBDir2 = 13;
    const int defaultPropSpeed = 200;
    const int turnSpeed = 100;
    const float thetaBuffer = 0.196;
    MissionHelper _mission;
    float degToRad(int deg);
};

#endif
