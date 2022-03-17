#ifndef MissionHelper_h
#define MissionHelper_h

#include "Arduino.h"

class MissionHelper
{
public:
	MissionHelper();
	void sendDutyCycle(int dutyCycle);
	void sendMagnetic(bool magnetic);
	int * updateCurrLocation();
private:
};

#endif
