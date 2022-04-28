#include "Arduino.h"
#include "MissionHelper.h"
#include "Enes100.h"

const static int wifiRX = 8;
const static int wifiTX = 9;
const static int arucoID = 999;

// WRAPPER FOR ENES100.H
MissionHelper::MissionHelper() {
}

// start method for wifi comms with vision system
// must call start to use wifi module
bool MissionHelper::start() {
	return Enes100.begin("Interstellar", DATA, arucoID, wifiTX, wifiRX);
}

// sends duty cycle param to vision system
void MissionHelper::sendDutyCycle(int dutyCycle) {
	Enes100.mission(CYCLE, dutyCycle);
}

// sends magnetic param to vision system
void MissionHelper::sendMagnetic(bool magnetic) {
	Enes100.mission(MAGNETISM, (magnetic) ? MAGNETIC : NOT_MAGNETIC);
}

// updates current location
bool MissionHelper::updateCurrLocation() {
	return Enes100.updateLocation();
}

// returns current X val of OTV
float MissionHelper::getX() {
	if(!updateCurrLocation()) {
    Enes100.println("Xsadge");
  }
	return Enes100.location.x;
}

// returns current Y val of OTV
float MissionHelper::getY() {
	if(!updateCurrLocation()) {
    Enes100.println("Ysadge");
	}
	return Enes100.location.y;
}

// returns current THETA val of OTV
float MissionHelper::getTheta() {
	while(!updateCurrLocation()) {
    Enes100.println("Tsadge");
    delay(30);
  }
	return Enes100.location.theta;
}

// sends param string to vision system
void MissionHelper::sendToVS(String in) {
  Enes100.println(in);
}

// prints curr location to vision system
void MissionHelper::printToVS() {
  Enes100.println(Enes100.location.x);
  Enes100.println(Enes100.location.y);
  Enes100.println(Enes100.location.theta);
}
