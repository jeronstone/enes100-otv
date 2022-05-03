#include "Arduino.h"
#include "Servo.h"
#include "ArmServo.h"

Servo servo;
const int armServoPin = 5;
const int forward = 1200;
const int backward = 1800;
const int stopFreq = 1500;

ArmServo::ArmServo() {
}

// method that starts servo
// did not work in constructor monkaS
// must call begin before using servo
void ArmServo::begin() {
  pinMode(armServoPin, OUTPUT);
  servo.attach(armServoPin);
  servo.writeMicroseconds(stopFreq);
}

void ArmServo::end() {
  servo.detach();
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
	servo.writeMicroseconds(stopFreq);
}

// runs arm servo down param direction for param time
// 1: down | 0: up
void ArmServo::runArm(bool dir, int time) {
  begin();
  (dir) ? runServoCW() : runServoCCW();
  delay(time);
  stopServoRotation();
  end();
}
