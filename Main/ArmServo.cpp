#include "Arduino.h"
#include "Servo.h"
#include "ArmServo.h"

Servo servo;
const int armServoPin = 5;
const int forward = 1000;
const int backward = 2000;
const int stop = 1500;
const int time = 1000; // change

ArmServo::ArmServo() {
}

void ArmServo::begin() {
  pinMode(armServoPin, OUTPUT);
  servo.attach(armServoPin);
  servo.writeMicroseconds(stop);
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
  delay(time);
  stopServoRotation();
}

void ArmServo::runArmUp() { // ' '
  runServoCW();
  delay(time);
  stopServoRotation();
}