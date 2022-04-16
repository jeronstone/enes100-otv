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
	return !digitalRead(A0);
}

bool Sensors::useReed() {
  int ti = millis();
  int hc = 0;
  int lc = 0;
  while (millis() - ti < 10000) {
    Serial.println(getReed());
    if (getReed()) {
      hc++;
    } else {
      lc++;
    }
  }

  return hc > lc;
}

bool Sensors::dutyCircuitReady() {
	return (pulseIn(missionCircuit, HIGH) == 0); // could be a yikes 
}

float Sensors::readDutyCycle() {
	float high = pulseIn(missionCircuit, HIGH);
	float low = pulseIn(missionCircuit, LOW);
	float t = high + low;
	return (high/t) * 100.0;
}
