#include "Propulsion.h"
#include "ArmServo.h"
#include "MissionHelper.h"
#include "Sensors.h"
//#include "Enes100.h"

void testing() {
  // PUT TESTING CODE HERE
}

// BELOW ARE PREDEFINED TESTING METHODS FOR MUCH OF THE SUBSYSTEMS
// ADD MORE AS NEEDED

// tests turning with vision system
void testTurnVS() {
  mission.printToVS();
  propulsion.turnTo(90);
  mission.sendToVS("SWAGGGGGG");
  delay(5000);
  propulsion.turnTo(0);
  while (1);
}

// tests reed sensor and sending to vision system
void testReed() {
  Serial.println("Starts in 5 sec");
  mission.sendToVS("Starts in 5 sec...");
  delay(5000);
  Serial.println("Start");
  mission.sendToVS("START");
  mission.sendToVS("Reading for 10 seconds...");
  Serial.println("FINAL" + String(sensors.useReed()));
  bool mag = sensors.useReed();
  mission.sendMagnetic(mag);
  while (1);
}

// tests and prints duty cycle
void testDuty() {
  Serial.println(sensors.readDutyCycle());
}

// tests wifi sending
void testWifiTX() {
  mission.sendToVS("Hi Vision System :)");
  String loc = String(mission.getX(), 3) + " " + String(mission.getY(), 3);
  mission.sendToVS("Our current XY location is: " + loc);
}

// tests wifi reciving
void testWifiRX() {
  String x = String(mission.getX(), 3);
  Serial.println("X loc: " + x);
  String y = String(mission.getY(), 3);
  Serial.println("Y loc: " + y);
  String t = String(mission.getTheta(), 3);
  Serial.println("T loc: " + t);
  delay(50);
}

// tests propulsion by driving forwards and backwards
void testProp() {
  propulsion.driveFwdS(255);
  delay(5000);
  propulsion.driveBackwdS(255);
  delay(5000);
  propulsion.stopMotors();
  delay(2000);
}

// tests servo going up and down
void testServo() {
  Serial.println("swag");
  armServo.runArmUp(0);
  delay(3000);
  armServo.runArmDown(200);
  delay(3000);
}

// tests and prints ultrasonic value
void testUS() {
  float x = sensors.getUltrasonic();
  Serial.println(x);
}
