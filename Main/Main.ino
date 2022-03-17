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
}

void loop() {
  
}
