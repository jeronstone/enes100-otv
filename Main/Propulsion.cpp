#include "Arduino.h"
#include "Propulsion.h"
#include "MissionHelper.h"

const int HBENA = 10;
const int HBENB = 11;
const int HBADir1 = 7;
const int HBBDir1 = 2;
const int HBADir2 = 6;
const int HBBDir2 = 13;

const int defaultPropSpeed = 200;
const int turnSpeed = 100;
const float thetaBuffer = 0.2618;

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

void Propulsion::driveFwd() {
  driveFwdS(defaultPropSpeed);
}

void Propulsion::driveFwdS(int speed) {
  digitalWrite(HBADir1, HIGH);
  digitalWrite(HBADir2, LOW);
  digitalWrite(HBBDir1, HIGH);
  digitalWrite(HBBDir2, LOW);
  analogWrite(HBENA, speed);
  analogWrite(HBENB, speed);
}

void Propulsion::driveBackwd() {
   driveBackwdS(defaultPropSpeed);
}

void Propulsion::driveBackwdS(int speed) {
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

void Propulsion::turnTo(int theta) {
  _mission.updateCurrLocation();
  int currTheta = _mission.getTheta();
  int t = degToRad(theta);
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
  _mission.updateCurrLocation();
  int currTheta = _mission.getTheta();
  while (!(currTheta - thetaBuffer >  degToRad(theta) + currTheta)) {
    digitalWrite(HBADir1, LOW);
    digitalWrite(HBADir2, LOW);
    digitalWrite(HBBDir1, HIGH);
    digitalWrite(HBBDir2, LOW);
    analogWrite(HBENB, turnSpeed);
    _mission.updateCurrLocation();
    int currTheta = _mission.getTheta();
  }
   stopMotors();
}

void Propulsion::turnRARight() {
   turnRight(90);
}

void Propulsion::turnRight(int theta) {
  _mission.updateCurrLocation();
  int currTheta = _mission.getTheta();
  while (!(currTheta + thetaBuffer > currTheta - degToRad(theta))) {
    digitalWrite(HBADir1, HIGH);
    digitalWrite(HBADir2, LOW);
    digitalWrite(HBBDir1, LOW);
    digitalWrite(HBBDir2, LOW);
    analogWrite(HBENA, turnSpeed);
    _mission.updateCurrLocation();
    int currTheta = _mission.getTheta();
  }
   stopMotors();
}

void Propulsion::turnAround() {
  _mission.updateCurrLocation();
  int currTheta = _mission.getTheta();
  if (currTheta > 0) {
    turnRight(180);
  } else {
    turnLeft(180);
  }
}

int Propulsion::degToRad(int deg) {
   return deg * 0.01745;
}
