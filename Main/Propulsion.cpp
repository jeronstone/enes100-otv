#include "Arduino.h"
#include "Propulsion.h"
#include "MissionHelper.h"

const int HBENA = 10;
const int HBENB = 11;
const int HBADir1 = 7;
const int HBBDir1 = 2;
const int HBADir2 = 6;
const int HBBDir2 = 13;

const int defaultPropSpeed = 100;
const int turnSpeed = 100;
const float thetaBuffer = 0.1;

MissionHelper _mission;

Propulsion::Propulsion(MissionHelper mission) {
  _mission = mission;
  pinMode(HBENA, OUTPUT);
  pinMode(HBENB, OUTPUT);
  pinMode(HBADir1, OUTPUT);
  pinMode(HBADir2, OUTPUT);
  pinMode(HBBDir1, OUTPUT);
  pinMode(HBBDir2, OUTPUT);
  stopMotors();
}

void Propulsion::driveBackwd() {
  driveBackwdS(defaultPropSpeed);
}

void Propulsion::driveBackwdS(int speed) {
  digitalWrite(HBADir1, HIGH);
  digitalWrite(HBADir2, LOW);
  digitalWrite(HBBDir1, HIGH);
  digitalWrite(HBBDir2, LOW);
  analogWrite(HBENA, speed);
  analogWrite(HBENB, speed);
}

void Propulsion::driveFwd() {
  driveFwdS(defaultPropSpeed);
}

void Propulsion::driveFwdS(int speed) {
  digitalWrite(HBADir1, LOW);
  digitalWrite(HBADir2, HIGH);
  digitalWrite(HBBDir1, LOW);
  digitalWrite(HBBDir2, HIGH);
  analogWrite(HBENA, speed);
  analogWrite(HBENB, speed);
}

void Propulsion::stopMotors() {
  digitalWrite(HBADir1, LOW);
  digitalWrite(HBADir2, LOW);
  digitalWrite(HBBDir1, LOW);
  digitalWrite(HBBDir2, LOW);
}

void Propulsion::turn90NoVS(bool dir) {
  if (dir) { //left
    digitalWrite(HBADir1, HIGH);
    digitalWrite(HBADir2, LOW);
    digitalWrite(HBBDir1, LOW);
    digitalWrite(HBBDir2, HIGH);
    analogWrite(HBENA, defaultPropSpeed);
    analogWrite(HBENB, defaultPropSpeed);
    delay(750);
  } else { //right
    digitalWrite(HBADir1, LOW);
    digitalWrite(HBADir2, HIGH);
    digitalWrite(HBBDir1, HIGH);
    digitalWrite(HBBDir2, LOW);
    analogWrite(HBENA, defaultPropSpeed);
    analogWrite(HBENB, defaultPropSpeed);
    delay(750);
  }
  stopMotors();
}

void Propulsion::turnTo(int theta) {
  //_mission.updateCurrLocation();
  float currTheta = _mission.getTheta();
  float t = degToRad(theta);
  _mission.sendToVS(String(t));
  if (t < currTheta) {
    turnRight(abs(currTheta - t));
  } else {
    turnLeft(abs(t - currTheta));
  }
}

void Propulsion::turnRALeft() {
  turnLeft(90);
}

void Propulsion::turnLeft(int theta) {
  //_mission.updateCurrLocation();
  float initTheta = _mission.getTheta();
  digitalWrite(HBADir1, HIGH);
  digitalWrite(HBADir2, LOW);
  digitalWrite(HBBDir1, LOW);
  digitalWrite(HBBDir2, HIGH);
  analogWrite(HBENA, defaultPropSpeed);
  analogWrite(HBENB, defaultPropSpeed);
  float currTheta = initTheta;
  while (!(currTheta - thetaBuffer >  theta + initTheta)) {
    //_mission.updateCurrLocation();
    currTheta = _mission.getTheta();
    _mission.sendToVS("CURR THETA: " + String(currTheta));
    _mission.sendToVS("TARGET THETA: " + String(theta + initTheta));
  }
  stopMotors();
}

void Propulsion::turnRARight() {
  turnRight(90);
}

void Propulsion::turnRight(int theta) {
  //_mission.updateCurrLocation();
  float initTheta = _mission.getTheta();
  digitalWrite(HBADir1, HIGH);
  digitalWrite(HBADir2, LOW);
  digitalWrite(HBBDir1, LOW);
  digitalWrite(HBBDir2, HIGH);
  analogWrite(HBENA, defaultPropSpeed);
  analogWrite(HBENB, defaultPropSpeed);
  float currTheta = initTheta;
  while (!(currTheta + thetaBuffer < initTheta - theta)) {
    //_mission.updateCurrLocation();
    currTheta = _mission.getTheta();
     _mission.sendToVS("CURR THETA: " + String(currTheta));
    _mission.sendToVS("TARGET THETA: " + String(theta + initTheta));
  }
  stopMotors();
}

void Propulsion::turnAround() {
  //_mission.updateCurrLocation();
  int currTheta = _mission.getTheta();
  if (currTheta > 0) {
    turnRight(180);
  } else {
    turnLeft(180);
  }
}

float Propulsion::degToRad(int deg) {
  return deg * 0.01745;
}
