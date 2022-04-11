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
	bool updateCurrLocation();
	float getX();
	float getY();
	float getTheta();
  void sendToVS(String in);
private:
	const static int wifiRX = 8;
	const static int wifiTX = 9;
	const static int arucoID = 5;
};

#endif
