#include "Propulsion.h"
#include "ArmServo.h"
#include "MissionHelper.h"
#include "Sensors.h"
//#include "Enes100.h"

MissionHelper mission;
ArmServo armServo;
Propulsion propulsion(mission);
Sensors sensors;

void setup() {
  Serial.begin(9600);
  
  Serial.println("Start Status: " + mission.start());
  Serial.println("Init loc update: " + mission.updateCurrLocation());
  //armServo.begin();
}

void loop() {
  //testServo();
  //testUS();
  //testProp();
  testWifi();
}

void testWifi() {
  Serial.println("X loc: " + mission.getX());
  Serial.println("Y loc: " + mission.getY());
  Serial.println("T loc: " + mission.getTheta());
  Serial.println(getX());
  delay(500);
  
}

void testProp() {
  propulsion.driveFwdS(255);
  delay(5000);
  propulsion.driveBackwdS(255);
  delay(5000);
  propulsion.stopMotors();
  delay(5000);
}

void testServo() {
  armServo.runServoCCW();
  delay(2000);
  armServo.runServoCW();
  delay(2000);
  armServo.stopServoRotation();
  delay(2000);
}

void testUS() {
  float x = sensors.getUltrasonic();
  Serial.println(x);
}
