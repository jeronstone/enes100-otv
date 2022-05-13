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
  return duration * 0.034 / 2.0;
}

// returns reed value
bool Sensors::getReed() {
  return !digitalRead(A0);
}

// takes average of reed value over 10 seconds
// this allows for errors to be discarded
bool Sensors::useReed() {
  int ti = millis();
  while (millis() - ti < 5000) {
    Serial.println(getReed());
    if (getReed()) {
      return 1;
    }
  }

  return 0;
}

// returns reed cycle read, "average" over 10 seconds
// calculation returns average of VALID values
// valid values are considered 
float Sensors::readDutyCycle() {
  int t = millis();
  int size = 50;
  float dutyRaw[size];
  int i = 0;
  while (i < size) {
    float high = pulseIn(missionCircuit, HIGH);
    float low = pulseIn(missionCircuit, LOW);
    float t = high + low;
    float val = (high / t) * 100.0;
    //return val;
    //Serial.println("VAL: " + String(val));
    if (val != 0.0 && val != 100.0 && round(val) % 10 == 0) {
      //Serial.println("VALID" + String(i));
      dutyRaw[i] = val;
      i++;
    }
  }

  float sum;
  for (int i = 0; i < size; i ++) {
    sum += dutyRaw[i];
  }

  return sum / (float) size;
}
