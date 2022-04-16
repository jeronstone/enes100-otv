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
  armServo.begin();
}

void loop() {
  testServo();
  //testUS();
  //testProp();
  //testWifiRX();
  //delay(500);
  //testWifiTX();
  //delay(500);
  //testHall();
  //testDuty();
  //delay(1000);
  //testNoVSTurn();
  //testReed();
  //testMagSensAndSend();
}

void testMagSensAndSend() {
  Serial.println("Starts in 5 sec");
  delay(5000);
  Serial.println("Start");
  bool mag = sensors.useReed();
  Serial.println(mag);
  mission.sendMagnetic(mag);
  Serial.println("Done");
  while(1);
}

void testNoVSTurn() {
  propulsion.turn90NoVS(1);
  delay(1000);
  propulsion.turn90NoVS(0);
  delay(1000);
  propulsion.turn90NoVS(1);
  delay(1000);
  while(1);
}

void testReed() {
  Serial.println("Starts in 5 sec");
  delay(5000);
  Serial.println("Start");
  Serial.println(sensors.useReed());
  while(1);
}

void testDuty() {
  Serial.println(sensors.readDutyCycle());
}

void testHall() {
  Serial.println(sensors.getHallEff());
}

void testWifiTX() {
  mission.sendToVS("Hi Vision System :)");
  String loc = String(mission.getX(), 3) + " " + String(mission.getY(), 3);
  mission.sendToVS("Our current XY location is: " + loc);
}

void testWifiRX() {
  String x = String(mission.getX(), 3);
  Serial.println("X loc: " + x);
  String y = String(mission.getY(), 3);
  Serial.println("Y loc: " + y);
  String t = String(mission.getTheta(), 3);
  Serial.println("T loc: " + t);
  delay(50);
}

void testProp() {
  propulsion.driveFwdS(255);
  delay(10000);
  //propulsion.driveBackwdS(255);
  //delay(5000);
  propulsion.stopMotors();
  delay(2000);
}

void testServo() {
  armServo.runServoCCW();
  delay(2000);
  armServo.stopServoRotation();
  armServo.runServoCW();
  delay(2000);
  armServo.stopServoRotation();
  delay(2000);
}

void testUS() {
  float x = sensors.getUltrasonic();
  Serial.println(x);
}
