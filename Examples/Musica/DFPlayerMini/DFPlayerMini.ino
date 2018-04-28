#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"

const int BAUDS = 9600;
const int MUSIC_RX_PIN = 50;
const int MUSIC_TX_PIN = 51;
const int MUSIC_VOLUME = 25; //Set volume value. From 0 to 30

DFRobotDFPlayerMini musicDFPlayer;
SoftwareSerial musicSoftwareSerial(MUSIC_RX_PIN, MUSIC_TX_PIN); // RX, TX

void setup() {

	  Serial.begin(BAUDS);

    musicSoftwareSerial.begin(BAUDS);
    if (!musicDFPlayer.begin(musicSoftwareSerial)) {
      while(true);
    }
    
    musicDFPlayer.volume(MUSIC_VOLUME);

    musicDFPlayer.play(1);
}

void loop() {
  Serial.println("hola");
}
