#ifndef MissionHelper_h
#define MissionHelper_h

#include "Arduino.h"

class MissionHelper
{
public:
	MissionHelper();
	bool start();
	void sendDutyCycle(int dutyCycle);
	void sendMagnetic(bool magnetic);
	void updateCurrLocation();
	int getX();
	int getY();
	int getTheta();
private:
	const static int arucoID;
	const static int wifiRX;
	const static int wifiTX;
	int loc[3];
};

#endif
