#ifndef Sensors_h
#define Sensors_h

#include "Arduino.h"

class Sensors
{
public:
	Sensors();
	float getUltrasonic();
	bool getReed();
	bool dutyCircuitReady();
	float readDutyCycle();
private:
	const int ultrasonicRX;
	const int ultrasonicTX;
	const int reedSwitch;
	const int missionCircuit;
};

#endif