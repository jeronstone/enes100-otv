#include "Arduino.h"
#include "Sensors.h"

const int ultrasonicRX = 4;
const int ultrasonicTX = 3;
const int missionCircuit = 12;

Sensors::Sensors() {
	pinMode(ultrasonicTX, OUTPUT);
	pinMode(ultrasonicRX, INPUT);
	pinMode(missionCircuit, INPUT);
}

float Sensors::getUltrasonic() {
	digitalWrite(ultrasonicTX, HIGH);
	delayMicroseconds(10);
	digitalWrite(ultrasonicTX, LOW);

	float duration = pulseIn(ultrasonicRX, HIGH);
	return duration * 0.034/2.0; // could be a yikes
}

bool Sensors::getReed() {
	return digitalRead(A0);
}

bool Sensors::getHallEff() {
	return !digitalRead(A0);
}

bool Sensors::dutyCircuitReady() {
	return (pulseIn(missionCircuit, HIGH) == 0); // could be a yikes 
}

float Sensors::readDutyCycle() {
	float high = pulseIn(missionCircuit, HIGH);
	float low = pulseIn(missionCircuit, LOW);
	float time = high + low;
	return (high/time) * 100.0;
}
