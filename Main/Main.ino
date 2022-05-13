#include "Propulsion.h"
#include "ArmServo.h"
#include "MissionHelper.h"
#include "Sensors.h"

MissionHelper mission;
ArmServo armServo;
Propulsion propulsion(mission);
Sensors sensors;

const float midpointY = 1.0; // 1 meter, we need to make sure this is right (enes100 library and stuff has lots of mistakes)
const float sidePointMissionSite = 0.84; // outer edge of mission zone
const float bottomObstacleField = 0.4; // theoretical "bottom" of obstacle field
const float southTopEdge = 0.8; // DISTANCE BEFORE ROBOT ARM IS HOVERING OVER DATA POINT
const float northBottomEdge = 1.1; // these are guesses :<
const float obstacleExists = 40; // cm, theoretical value that an object exists if ultrasonic sensor value reads <= to this value
const int timeToClearObstacleY = 200; // ms, time until the robot has cleared an obstacle in the y dir
const int timeToClearObstacleX = 1650; // ms, time until the robot has cleared an obstacle in the x dir
const float limboMidPoint = 1.3; // Y coord of midpoint of limbo
const int timeToClearLimbo = 2500; // time to clear limbo
const int upTime = 2750;
const int downTime = 2600;
float dutyCycle;
bool magnetic;
bool doMissionArmStuff;

void setup() {
  Serial.begin(9600);
  startMission(); // IF NO WIFI CONNECTION NEEDED FOR TESTING, COMMENT OUT
  //delay(10000); //testing line to delay start for uploading
  Serial.println(u8"\U0001f4aa");
  doMissionArmStuff = 0;
}

// starts mission stuff
void startMission() {
  while (!mission.start()) {
    //Serial.println("WIFI FAIL ...");
  }
  mission.sendToVS("CONNECTED");
  mission.sendToVS(u8"\U0001f4aa");
  mission.updateCurrLocation();
  mission.sendToVS("INIT LOCATION: ");
  mission.printToVS();
  Serial.println("Start Status: " + mission.start());
  Serial.println("Init loc update: " + mission.updateCurrLocation());
}

void loop() { // if testing, comment out realMission() and run testing()
  realMission();
  //testing();
  // write testing code in testing() method found below nav methods
}

void realMission() {
  doMission((mission.getY() > midpointY));
  //if the y position is greater than the midpoint, then the robot is on the north side and the mission is on the south side. else, vice versa.
  mission.sendToVS("mission is done");
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
  //String northsouth = ((robotIsNorth) ? "north" : "south");
  //mission.sendToVS("we are " + northsouth);
  mission.updateCurrLocation();
  //armServo.runArm(UP, upTime);
  float slope = 0.0;
  float theta = 0.0;
  if (robotIsNorth) {
    propulsion.turnTo(-PI / 2);
    mission.updateCurrLocation();
    propulsion.turnTo(-PI / 2);
    //mission.sendToVS("we should be facing -pi/2 Clueless");
    mission.updateCurrLocation();
    slope = (mission.getY() - 0.55) / (mission.getX() - 0.55);
    if (slope < 0) {
      theta = - atan(abs(slope));
    } else {
      theta = - (PI - atan(abs(slope)));
    }
    mission.updateCurrLocation();
    propulsion.turnTo(theta);
    while (mission.getY() > southTopEdge) {   // POINT AT WHICH ARM IS HOVERING OVER MIDPOINT OF DATA EXTRACTION POINT
      //mission.sendToVS("driving to south edge!");
      propulsion.driveFwd();
      mission.updateCurrLocation();
    }
    propulsion.stopMotors();
    mission.updateCurrLocation();

  } else {
    propulsion.turnTo(PI / 2);
    mission.updateCurrLocation();
    propulsion.turnTo(PI / 2);
    //mission.sendToVS("we should be facing pi/2 Clueless");
    mission.updateCurrLocation();
    slope = (mission.getY() - 1.45) / (mission.getX() - 0.55);
     if (slope < 0) {
      theta = PI - atan(abs(slope));
     } else {
      theta = atan(abs(slope));
     }
     mission.updateCurrLocation();
     propulsion.turnTo(theta);
    while (mission.getY() < northBottomEdge) { // POINT AT WHICH ARM IS HOVERING OVER MIDPOINT OF DATA EXTRACTION POINT
      //mission.sendToVS("driving to north edge!");
      propulsion.driveFwd();
      mission.updateCurrLocation();
    }
    propulsion.stopMotors();
    mission.updateCurrLocation();
  }
  

  
  //mission.sendToVS("we should be at the mission site Clueless");

  float distance = 0.0;
  if(robotIsNorth) {
    distance = (sqrt(pow(mission.getX()-0.55, 2.0) + pow(mission.getY()-1.45, 2.0)));
  } else {
    distance = (sqrt(pow(mission.getX()-0.55, 2.00) + pow(mission.getY()-0.55, 2.0)));
  }
  if (doMissionArmStuff) {
    // doing the mission stuff
    armServo.runArm(DOWN, downTime);
    propulsion.driveBackwd();
    delay(100);
    propulsion.stopMotors();
    float duty = sensors.readDutyCycle();
    mission.sendDutyCycle(duty);
    bool reed = sensors.useReed();
    mission.sendMagnetic(reed);
    armServo.runArm(UP, upTime);
  }
  //mission.sendToVS("now we should be done with mission sensing Clueless");
  // navigate to center of field
  if (robotIsNorth) { // robot WAS north, and is now south
    while (mission.getY() < midpointY) {
      //mission.sendToVS("we should be moving towards midpointY");
      propulsion.driveBackwd();
      mission.updateCurrLocation();
    }
  } else {          // robot WAS south, and is now north
    while (mission.getY() > midpointY) {
      //mission.sendToVS("we should be moving towards midpointY");
      propulsion.driveBackwd();
      mission.updateCurrLocation();
    }
  }
  propulsion.stopMotors();
  mission.updateCurrLocation();

  // navigate to side edge of mission site
  armServo.runArm(DOWN, downTime);
  propulsion.turnTo(0);

  // mission.sendToVS("we should now be facing 0");
  mission.updateCurrLocation();
  while (mission.getX() < sidePointMissionSite) {
    propulsion.driveFwd();
    mission.updateCurrLocation();
  }
  //mission.sendToVS("we should now be ready for nav (at the sidepointmissionsite");
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
  while (mission.getY() < (limboMidPoint)) {
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
  mission.sendToVS(u8"\U0001f44a");
  while (1);
}

void testing() {
  armServo.runArm(UP, upTime);
  while (1);
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
  Serial.println("FINAL DUTY CYCLE: " + String(sensors.readDutyCycle()));
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
  armServo.runArm(UP, 2000);
  delay(3000);
  armServo.runArm(DOWN, 200);
  delay(3000);
}

// tests and prints ultrasonic value
void testUS() {
  float x = sensors.getUltrasonic();
  Serial.println(x);
}
