#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;

void setup()
{
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  while (!Serial);
  if (!SD.begin(SD_ChipSelectPin))
  {
    Serial.println("SD fail");
    return;
  }
  Serial.println("SUCCESS");
  tmrpcm.setVolume(7);
  tmrpcm.play("Interstellar.wav");
}

void loop() {

}
