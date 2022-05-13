#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"

class Sensors
{
public:
	Sensors();
	float getUltrasonic();
	bool getReed();
	float readDutyCycle();
  bool useReed();
private:
	const int ultrasonicRX = 4;
	const int ultrasonicTX = 3;
	const int missionCircuit = 12;
};

#endif
