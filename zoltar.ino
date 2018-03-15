#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Configuration.h"
#include "StatusInit.h"
#include "StatusStandBy.h"
#include "StatusActivateGame.h"

int status;

void setup() {    
    Serial.begin(BAUDS);
    
    initMusicConfiguration();
    initSoundConfiguration();
    
    pinMode(DETECT_COIN_PIN, INPUT);
    pinMode(BACKGROUND_LED_PIN, OUTPUT);
    pinMode(EYES_LED_PIN, OUTPUT);
    pinMode(POINT_TO_MOUTH_LED_PIN, OUTPUT);
    pinMode(PUSH_BUTTON_COIN_LED_PIN, OUTPUT);

    status = STATUS_STAND_BY;
} 

void loop() {
  
  printStatus();

  switch (status) {

    case STATUS_INIT:
      status = statusInit(status);
      break;

    case STATUS_ACTIVATE_GAME:
      status = statusActivateGame(status);
      break;

    case STATUS_WAITING_RELEASE_COIN:
      //unsigned long timeLoop = millis();
      
      // Esperamos 10 segundos comprobando si se ha pulsado el botón de "liberar moneda"
      // Cuando se ha pulsado el botón o hayan pasado los 10 segundos, se libera la moneda.
      // Activo siguiente estado WIN_OR_LOST
      
      // Botón Liberar moneda - 1 digital input
      // Servo libera moneta depués del tiempo - 1 digital input

      break;

    case STATUS_WIN_OR_LOST:
      // Chequeamos los sensores de acierto o no
      // Si ha acertado pasamos a "WIN" sino a "LOST"

      // Sensores acierto o no - 2 digital inputs
      break;

    case STATUS_WIN:
        // Sacar tarjeta Acierto
        // Activar siguiente estado OFF

        // Servo tarjetero 1 - 1 digital input
      break;

    case STATUS_LOST:
        // Sacar tarjeta de la tienda
        // Activar siguiente estado OFF

        // Servo tarjetero 2 - 1 digital input
      break;

    case STATUS_OFF:
        // Esperar a que termine la música
        // desactivar musica y luces y movimiento. Todo
        // Activar siguiente estado STAND_BY

      break;

    default: //case "STAND_BY":
      status = statusStandBy(status);
      break;

  }
}


void printStatus() {
  String statusText = "STAND_BY";

  switch (status) {
    
    case STATUS_INIT:
      statusText = "INIT";
    break;
    case STATUS_ACTIVATE_GAME:
      statusText = "ACTIVATE_GAME";
    break;
    case STATUS_WAITING_RELEASE_COIN:
      statusText = "WAITING_RELEASE_COIN";
    break;
    case STATUS_WIN_OR_LOST:
      statusText = "WIN_OR_LOST";
    break;
    case STATUS_WIN:
      statusText = "WIN";
    break;
    case STATUS_LOST:
      statusText = "LOST";
    break;
    case STATUS_OFF:
      statusText = "OFF";
    break;
    default:
      statusText = "STAND_BY";
    break;
  }

  unsigned long timeLoop = millis();
  Serial.println("STATUS :" + statusText + " - " + timeLoop);
}

