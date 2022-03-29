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
	const int forward = 1000;
	const int backward = 2000;
	const int stop = 1500;
	const int time = 1000;
};

#endif