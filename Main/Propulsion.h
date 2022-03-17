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
private:
	const int HBENA;
	const int HBENB;
	const int HBADir1;
	const int HBBDir1;
	const int HBADir2;
	const int HBBDir2;
	const int defaultPropSpeed;
	const int turnSpeed;
	const float thetaBuffer;
	MissionHelper _mission;
	int degToRad(int deg);
};

#endif
