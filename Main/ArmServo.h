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
	void runArmDown(int time);
	void runArmUp(int time);
private:
	Servo servo;
	const int armServoPin = 5;
	const int forward = 1200;
	const int backward = 1800;
	const int stop = 1500;
};

#endif
