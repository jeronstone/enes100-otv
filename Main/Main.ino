#include "Propulsion.h"
#include "ArmServo.h"
#include "MissionHelper.h"
#include "Sensors.h"

MissionHelper mission;
ArmServo armServo;
Propulsion propulsion(mission);
Sensors sensors;

void setup() {
  //mission.start();
  //mission.updateCurrLocation();
  armServo.begin();
}

void loop() {
  //testServo();
}

void testServo() {
  armServo.runServoCCW();
  delay(2000);
  armServo.runServoCW();
  delay(2000);
  armServo.stopServoRotation();
  delay(2000);
}
