#ifndef ArmServo_h
#define ArmServo_h

#include "Arduino.h"
#include "Servo.h"

class ArmServo
{
public:
	ArmServo();
	void begin();
	void runServoCCW();
	void runServoCW();
	void stopServoRotation();
	void runArmDown();
	void runArmUp();
private:
	Servo servo;
	const int armServoPin = 5;
	const int forward = 1250;
	const int backward = 1750;
	const int stop = 1500;
	const int time = 2000; // change
};

#endif
