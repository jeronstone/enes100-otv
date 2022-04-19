#include "Tank.h"
#include "Enes100.h"

const float thetaBuffer = 0.196;
const int arucoID = 13;

void loop() {
  Enes100.println(Enes100.location.x);
  Enes100.println(Enes100.location.y);
  Enes100.println(Enes100.location.theta);
  turnTo(90);
}

void setup() {
  Serial.begin(9600);
  Enes100.begin("Interstellar", DATA, arucoID, 10, 11);
  Tank.begin();
}

void turnTo(int theta) {
  Enes100.updateLocation();
  int currTheta = degToRad(Enes100.location.theta);
  int t = degToRad(theta);
  Enes100.println("Init theta: " + currTheta);
  Enes100.println("Taget theta: " + t);
  if (t < currTheta) {
    turnRight(abs(currTheta - t));
  } else {
    turnLeft(abs(t - currTheta));
  }
}

void turnLeft(int theta) {
  Enes100.updateLocation();
  int currTheta = degToRad(Enes100.location.theta);
  Enes100.println("INITIAL TEST " + String(Enes100.location.theta));
  Tank.setLeftMotorPWM(200);
  while (!(currTheta - thetaBuffer >  degToRad(theta) + currTheta)) {
    Enes100.updateLocation();
    int currTheta = degToRad(Enes100.location.theta);
    Enes100.println("Curr theta: " + currTheta);
  }
  Tank.turnOffMotors();
}


void turnRight(int theta) {
  Enes100.updateLocation();
  int currTheta = degToRad(Enes100.location.theta);
  Enes100.println("INITIAL TEST " + String(Enes100.location.theta));
  Tank.setRightMotorPWM(200);
  while (!(currTheta + thetaBuffer > currTheta - degToRad(theta))) {
    Enes100.updateLocation();
    int currTheta = degToRad(Enes100.location.theta);
    Enes100.println("Curr theta: " + currTheta);
  }
  Tank.turnOffMotors();
}

float degToRad(int deg) {
  return ((float)deg) * 0.01745;
}
