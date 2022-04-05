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
  
  //Serial.println("Start Status: " + mission.start());
  //Serial.println("Init loc update: " + mission.updateCurrLocation());
  //armServo.begin();
}

void loop() {
  //testServo();
  //testUS();
  //testProp();
  //testWifi();
  //testHall();
  testDuty();
  delay(1000);
}

void testDuty() {
  Serial.println(sensors.readDutyCycle());
}

void testHall() {
  Serial.println(sensors.getHallEff());
}

void testWifi() {
  String x = String(mission.getX(), 3);
  Serial.println("X loc: " + x);
  String y = String(mission.getY(), 3);
  Serial.println("Y loc: " + y);
  String t = String(mission.getTheta(), 3);
  Serial.println("T loc: " + t);
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
