#include "Arduino.h"
#include "Servo.h"
#include "ArmServo.h"

Servo servo;
const int armServoPin = 5;
const int forward = 1000;
const int backward = 2000;
const int stop = 1500;

ArmServo::ArmServo() {
	servo.attach(armServoPin);
}

void ArmServo::runServoCCW() {
	servo.writeMicroseconds(forward);
}

void ArmServo::runServoCW() {
	servo.writeMicroseconds(backward);
}

void ArmServo::stopServoRotation() {
	servo.writeMicroseconds(stop);
}

void ArmServo::runArmDown() { // MAYBE SWTICH
  runServoCCW();
  //TODO delay(speedOfServo/armDist);
  stopServoRotation();
}

void ArmServo::runArmUp() { // ' '
  runServoCW();
  //TODO delay(speedOfServo/armDist);
  stopServoRotation();
}