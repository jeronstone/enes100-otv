#include "Arduino.h"
#include "MissionHelper.h"
#include "Enes100.h"

MissionHelper::MissionHelper() {

}

void MissionHelper::sendDutyCycle(int dutyCycle) {
	Enes100.mission(CYCLE, dutyCycle);
}

void MissionHelper::sendMagnetic(bool magnetic) {
	Enes100.mission(MAGNETISM, (magnetic) ? MAGNETIC : NOT_MAGNETIC);
}

int * MissionHelper::updateCurrLocation() {
	int loc[3];
	if (Enes100.updateLocation()) {
		loc[0] = Enes100.location.x;
    	loc[1] = Enes100.location.y; 
    	loc[2] = Enes100.location.theta; 
	}

	return loc;
}