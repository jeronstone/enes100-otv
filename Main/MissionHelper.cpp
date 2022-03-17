#include "Arduino.h"
#include "MissionHelper.h"
#include "Enes100.h"

const static int wifiRX = 8;
const static int wifiTX = 9;
const static int arucoID = 1;

int loc[3];

MissionHelper::MissionHelper() {
}

bool MissionHelper::start() {
	Enes100.begin("Interstellar", DATA, arucoID, wifiRX, wifiTX);
}

void MissionHelper::sendDutyCycle(int dutyCycle) {
	Enes100.mission(CYCLE, dutyCycle);
}

void MissionHelper::sendMagnetic(bool magnetic) {
	Enes100.mission(MAGNETISM, (magnetic) ? MAGNETIC : NOT_MAGNETIC);
}

void MissionHelper::updateCurrLocation() {
	if (Enes100.updateLocation()) {
		loc[0] = Enes100.location.x;
    	loc[1] = Enes100.location.y; 
    	loc[2] = Enes100.location.theta; 
	}

	return loc;
}

int MissionHelper::getX() {
	return loc[0];
}

int MissionHelper::getY() {
	return loc[1];
}

int MissionHelper::getTheta() {
	return loc[2];
}