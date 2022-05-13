#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;

void setup()
{
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  //while (!Serial);
  if (!SD.begin(SD_ChipSelectPin))
  {
    Serial.println("SD fail");
    return;
  }
  Serial.println("SUCCESS");
  tmrpcm.setVolume(5);
  tmrpcm.play((char*)"audio.WAV", 60);
  while(1) {
    if (tmrpcm.isPlaying()) {
      Serial.println("PLAYING...");
    } else {
      Serial.println("NOT PLAYING...");
    }
  }
}

void loop() {

}
