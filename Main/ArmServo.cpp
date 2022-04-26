#include "Arduino.h"
#include "Servo.h"
#include "ArmServo.h"

Servo servo;
const int armServoPin = 5;
const int forward = 1200;
const int backward = 1800;
const int stop = 1500;

ArmServo::ArmServo() {
}

// method that starts servo
// did not work in constructor monkaS
// must call begin before using servo
void ArmServo::begin() {
  pinMode(armServoPin, OUTPUT);
  servo.attach(armServoPin);
  servo.writeMicroseconds(stop);
}

// runs servo in counter clock wise direction
void ArmServo::runServoCCW() {
	servo.writeMicroseconds(forward);
}

// runs servo in clock wise direction
void ArmServo::runServoCW() {
	servo.writeMicroseconds(backward);
}

// stops rotation of servo motor
void ArmServo::stopServoRotation() {
	servo.writeMicroseconds(stop);
}

// runs arm servo up for param time
void ArmServo::runArmUp(int time) {
  runServoCCW();
  delay(time);
  stopServoRotation();
}

// runs arm servo down for param town
void ArmServo::runArmDown(int time) {
  runServoCW();
  delay(time);
  stopServoRotation();
}
