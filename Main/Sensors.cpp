#include "Arduino.h"
#include "Sensors.h"

const int ultrasonicRX = 4;
const int ultrasonicTX = 3;
const int reedSwitch = A0;
const int missionCircuit = 12;

Sensors::Sensors() {
}

float Sensors::getUltrasonic() {
	digitalWrite(ultrasonicTX, HIGH);
	delayMicroseconds(10);
	digitalWrite(ultrasonicTX, LOW);

	float duration = pulseIn(ultrasonicRX, HIGH);
	return duration * 0.034/2.0; // could be a yikes
}

bool Sensors::getReed() {
	return digitalRead(reedSwitch);
}

bool Sensors::dutyCircuitReady() {
	return (pulseIn(missionCircuit, HIGH) == 0); // could be a yikes 
}

float Sensors::readDutyCycle() {
	int high = pulseIn(missionCircuit, HIGH);
	int low = pulseIn(missionCircuit, LOW);
	int time = high + low;
	return ((float) high)/((float) time);
}