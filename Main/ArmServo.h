#ifndef ArmServo_h
#define ArmServo_h

#include "Arduino.h"
#include "Servo.h"

class ArmServo
{
public:
	ArmServo();
	void runArmDown();
	void runArmUp();
private:
	void runServoCCW();
	void runServoCW();
	void stopServoRotation();
	Servo servo;
	const int armServoPin;
};

#endif