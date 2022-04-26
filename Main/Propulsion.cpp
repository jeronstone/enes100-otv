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
const int turnSpeed = 50;
const float thetaBuffer = 0.25;

MissionHelper _mission;

// propulsion system with param mission wrapper
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

// sends OTV backwards at default speed
void Propulsion::driveBackwd() {
  driveBackwdS(defaultPropSpeed);
}

// sends OTV backwards at param speed
void Propulsion::driveBackwdS(int speed) {
  digitalWrite(HBADir1, HIGH);
  digitalWrite(HBADir2, LOW);
  digitalWrite(HBBDir1, HIGH);
  digitalWrite(HBBDir2, LOW);
  analogWrite(HBENA, speed);
  analogWrite(HBENB, speed);
}

// sends OTV forward at default speed
void Propulsion::driveFwd() {
  driveFwdS(defaultPropSpeed);
}

// sends OTV forwards at param speed
void Propulsion::driveFwdS(int speed) {
  digitalWrite(HBADir1, LOW);
  digitalWrite(HBADir2, HIGH);
  digitalWrite(HBBDir1, LOW);
  digitalWrite(HBBDir2, HIGH);
  analogWrite(HBENA, speed);
  analogWrite(HBENB, speed);
}

// stops OTV
void Propulsion::stopMotors() {
  digitalWrite(HBADir1, LOW);
  digitalWrite(HBADir2, LOW);
  digitalWrite(HBBDir1, LOW);
  digitalWrite(HBBDir2, LOW);
}

// turns OTV left
void Propulsion::sendMotorsLeft() {
  digitalWrite(HBADir1, HIGH);
  digitalWrite(HBADir2, LOW);
  digitalWrite(HBBDir1, LOW);
  digitalWrite(HBBDir2, HIGH);
  analogWrite(HBENA, turnSpeed);
  analogWrite(HBENB, turnSpeed);
}

// turns OTV right
void Propulsion::sendMotorsRight() {
  digitalWrite(HBADir1, LOW);
  digitalWrite(HBADir2, HIGH);
  digitalWrite(HBBDir1, HIGH);
  digitalWrite(HBBDir2, LOW);
  analogWrite(HBENA, turnSpeed);
  analogWrite(HBENB, turnSpeed);
}

// turns OTV to param theta
void Propulsion::turnTo(float targetTheta) {
  float currTheta = _mission.getTheta();
  bool swag = false;
  if (currTheta - targetTheta > 0) {
    sendMotorsRight();
  } else {
    sendMotorsLeft();
    swag = true;
  }
  
  while (abs(currTheta - targetTheta) > thetaBuffer) {
    currTheta = _mission.getTheta();
    delay(30);
  }
  
  stopMotors();
  delay(500);
  
  //if (swag) {
  //  sendMotorsRight();
  //  delay(500);
  //}
  //stopMotors();
}

// converts degrees to radians
// probably not needed/used but im keeping it just in case :)
float Propulsion::degToRad(int deg) {
  return deg * 0.01745;
}
