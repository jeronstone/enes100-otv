#include "Propulsion.h"
#include "ArmServo.h"
#include "MissionHelper.h"
#include "Sensors.h"
//#include "Enes100.h"

MissionHelper mission;
ArmServo armServo;
Propulsion propulsion(mission);
Sensors sensors;

double midpointY = 1.0; // 1 meter, we need to make sure this is right (enes100 library and stuff has lots of mistakes)
double sidePointMissionSite = 0.2; // outer edge of mission zone
double bottomObstacleField = 0.6; // theoretical "bottom" of obstacle field
double southTopEdge = 0.8; // dISTANCE BEFORE ROBOT ARM IS HOVERING OVER DATA POINT
double northBottomEdge = 1.2; // these are guesses :<
double obstacleExists = 40; // cm, theoretical value that an object exists if ultrasonic sensor value reads <= to this value
int timeToClearObstacleY = 250; // ms, time until the robot has cleared an obstacle in the y dir
int timeToClearObstacleX = 1500; // ms, time until the robot has cleared an obstacle in the x dir
double limboMidPoint = 1.5; // Y coord of midpoint of limbo
int timeToClearLimbo = 2500; // time to clear limbo
double dutyCycle;
boolean magnetic;

void setup() {
  Serial.begin(9600);
  startMission(); // IF NO WIFI CONNECTION NEEDED FOR TESTING, COMMENT OUT
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
  realMission();
  //testing(); // write testing code in testing() method found in Test.ino
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
  armServo.runArmUp(2750);
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
  armServo.runArmDown(2750);
  sensors.dutyCircuitReady();
  mission.sendDutyCycle(sensors.readDutyCycle());
  mission.sendMagnetic(sensors.useReed());
  armServo.runArmUp(2750);

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
  armServo.runArmDown(2750);
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
  while (true) {
    //nothing
  }
}
