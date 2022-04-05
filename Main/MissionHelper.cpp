#include "Arduino.h"
#include "MissionHelper.h"
#include "Enes100.h"

const static int wifiRX = 8;
const static int wifiTX = 9;
const static int arucoID = 6;

MissionHelper::MissionHelper() {
}

bool MissionHelper::start() {
	return Enes100.begin("Interstellar", DATA, arucoID, wifiTX, wifiRX);
}

void MissionHelper::sendDutyCycle(int dutyCycle) {
	Enes100.mission(CYCLE, dutyCycle);
}

void MissionHelper::sendMagnetic(bool magnetic) {
	Enes100.mission(MAGNETISM, (magnetic) ? MAGNETIC : NOT_MAGNETIC);
}

bool MissionHelper::updateCurrLocation() {
	return Enes100.updateLocation();
}

float MissionHelper::getX() {
	if(!updateCurrLocation()) {
    Serial.println("Xsadge");
  }
	return Enes100.location.x;
}

float MissionHelper::getY() {
	if(!updateCurrLocation()) {
    Serial.println("Ysadge");
	}
	return Enes100.location.y;
}

float MissionHelper::getTheta() {
	if(!updateCurrLocation()) {
    Serial.println("Tsadge");
  }
	return Enes100.location.theta;
}
