#include "Propulsion.h"
#include "ArmServo.h"
#include "MissionHelper.h"
#include "Sensors.h"
//#include "Enes100.h"

MissionHelper mission;
ArmServo armServo;
Propulsion propulsion(mission);
Sensors sensors;

const double midpointY = 1.0; // 1 meter, we need to make sure this is right (enes100 library and stuff has lots of mistakes)
const double sidePointMissionSite = 0.2; // outer edge of mission zone
const double bottomObstacleField = 0.6; // theoretical "bottom" of obstacle field
const double southTopEdge = 0.8; // dISTANCE BEFORE ROBOT ARM IS HOVERING OVER DATA POINT
const double northBottomEdge = 1.2; // these are guesses :<
const double obstacleExists = 40; // cm, theoretical value that an object exists if ultrasonic sensor value reads <= to this value
const int timeToClearObstacleY = 250; // ms, time until the robot has cleared an obstacle in the y dir
const int timeToClearObstacleX = 1500; // ms, time until the robot has cleared an obstacle in the x dir
const double limboMidPoint = 1.5; // Y coord of midpoint of limbo
const int timeToClearLimbo = 2500; // time to clear limbo
const int upTime = 3800;
const int downTime = 3800;
double dutyCycle;
boolean magnetic;

void setup() {
  Serial.begin(9600);
  //startMission(); // IF NO WIFI CONNECTION NEEDED FOR TESTING, COMMENT OUT
  armServo.begin();
  delay(10000);
  Serial.println(u8"\U0001f4aa");
}

// starts mission stuff
void startMission() {
  while (!mission.start());
  mission.sendToVS("CONNECTED");
  mission.updateCurrLocation();
  mission.printToVS();
  Serial.println("Start Status: " + mission.start());
  Serial.println("Init loc update: " + mission.updateCurrLocation());
}

void loop() { // if testing, comment out realMission() and run testing()
  //realMission();
  testing(); // write testing code in testing() method found in Test.ino
}

void realMission() {
  mission.updateCurrLocation();

  doMission((mission.getY() > midpointY));
  //if the y position is greater than the midpoint, then the robot is on the north side and the mission is on the south side. else, vice versa.

  // nav code
  prepareNav();
  findHole();
  prepareNav();
  findHole();
  clearLimbo();

  // runs infinite while loop
  finish();
  // pog
}

void doMission(boolean robotIsNorth) { // true if north, false if south
  mission.updateCurrLocation();
  //armServo.runArmUp(upTime);
  if (robotIsNorth) {
    propulsion.turnTo(-PI / 2);
    mission.updateCurrLocation();
    while (mission.getY() > southTopEdge) {   // POINT AT WHICH ARM IS HOVERING OVER MIDPOINT OF DATA EXTRACTION POINT
      propulsion.driveFwd();
      mission.updateCurrLocation();
    }
    propulsion.stopMotors();
    mission.updateCurrLocation();
  } else {
    propulsion.turnTo(PI / 2);
    mission.updateCurrLocation();
    while (mission.getY() < northBottomEdge) { // POINT AT WHICH ARM IS HOVERING OVER MIDPOINT OF DATA EXTRACTION POINT
      propulsion.driveFwd();
      mission.updateCurrLocation();
    }
    propulsion.stopMotors();
    mission.updateCurrLocation();
  }

  // doing the mission stuff
  armServo.runArmDown(downTime);
  sensors.dutyCircuitReady();
  float duty = sensors.readDutyCycle();
  mission.sendDutyCycle(duty);
  bool reed = sensors.useReed();
  mission.sendMagnetic(reed);
  armServo.runArmUp(upTime);

  // navigate to center of field
  if (robotIsNorth) { // robot WAS north, and is now south
    while (mission.getY() < midpointY) {
      propulsion.driveBackwd();
      mission.updateCurrLocation();
    }
  } else {          // robot WAS south, and is now north
    while (mission.getY() > midpointY) {
      propulsion.driveBackwd();
      mission.updateCurrLocation();
    }
  }
  propulsion.stopMotors();
  mission.updateCurrLocation();

  // navigate to side edge of mission site
  armServo.runArmDown(downTime);
  propulsion.turnTo(0);
  mission.updateCurrLocation();
  while (mission.getX() < sidePointMissionSite) {
    propulsion.driveFwd();
    mission.updateCurrLocation();
  }
  propulsion.stopMotors();
  mission.updateCurrLocation();

}

void prepareNav() {
  propulsion.turnTo(PI / 2);
  mission.updateCurrLocation();
  while (mission.getY() > bottomObstacleField) {
    propulsion.driveBackwd();
    mission.updateCurrLocation();
  }
  propulsion.stopMotors();
  mission.updateCurrLocation();
  propulsion.turnTo(PI / 2);
}
void findHole() {
  while (sensors.getUltrasonic() < obstacleExists) {
    mission.sendToVS(String(sensors.getUltrasonic()));
    propulsion.driveFwd();
    mission.updateCurrLocation();
    delay(30);
  }
  propulsion.stopMotors();
  mission.updateCurrLocation();

  propulsion.driveFwd();
  delay(timeToClearObstacleY);
  propulsion.stopMotors();
  mission.updateCurrLocation();

  propulsion.turnTo(0);
  mission.updateCurrLocation();
  propulsion.driveFwd();
  delay(timeToClearObstacleX);
  propulsion.stopMotors();
  mission.updateCurrLocation();
}

void clearLimbo() {
  propulsion.turnTo(PI / 2);
  mission.updateCurrLocation();
  while (mission.getY() < limboMidPoint) {
    propulsion.driveFwd();
    mission.updateCurrLocation();
  }
  propulsion.stopMotors();

  propulsion.turnTo(0);
  mission.updateCurrLocation();
  propulsion.driveFwd();
  delay(timeToClearLimbo);
  propulsion.stopMotors();
  mission.updateCurrLocation();
}

void finish() {
  mission.sendToVS(u8"\U0001f4aa");
  while (true) {
    //nothing
  }
}
