#include "Tank.h"
#include "Enes100.h"

void setup() {
  Serial.begin(9600);
  Enes100.begin("Interstellar", DATA, 13, 10, 11);
  Tank.begin();
}

void loop() {
  Enes100.println(Enes100.location.x);
  Enes100.println(Enes100.location.y);
  Enes100.println(Enes100.location.theta);
  Serial.println(Enes100.location.x);
  Serial.println(Enes100.location.y);
  Serial.println(Enes100.location.theta);

}
