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

// returns ultrasonic value
float Sensors::getUltrasonic() {
  digitalWrite(ultrasonicTX, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTX, LOW);

  float duration = pulseIn(ultrasonicRX, HIGH);
  return duration * 0.034 / 2.0; // could be a yikes
}

// returns reed value
bool Sensors::getReed() {
  return !digitalRead(A0);
}

// takes average of reed value over 10 seconds
// this allows for errors to be discarded
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

// returns true if duty cycle is read to be read
// lowkey don't call this cuz this may be accounter for in read duty method later
bool Sensors::dutyCircuitReady() {
  return (pulseIn(missionCircuit, HIGH) == 0); // could be a yikes
}

// returns reed cycle read, "average" over 10 seconds
// calculation returns average of VALID values
// valid values are considered 
float Sensors::readDutyCycle() {
  float dutyRaw[100];
  int i = 0;
  while (i < 100) {
    float high = pulseIn(missionCircuit, HIGH);
    float low = pulseIn(missionCircuit, LOW);
    float t = high + low;
    float val = (high / t) * 100.0;
    //return val;
    Serial.println("VAL: " + String(val));
    if (val != 0.0 && val != 100.0 && round(val) % 10 == 0) {
      Serial.println("VALID" + String(i));
      dutyRaw[i] = val;
      i++;
    }
  }

  float sum;
  for (int i = 0; i < 100; i ++) {
    sum += dutyRaw[i];
  }

  return sum / 100.0;
}
