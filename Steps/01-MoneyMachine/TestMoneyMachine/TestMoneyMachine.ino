#include "Arduino.h"
#include "Configuration.h"
#include "StatusStandBy.h"

int status;

void setup()
{
  Serial.println("00000000");
  Serial.begin(BAUDS);

  Serial.println("1");
  initializePins();
  Serial.println("2");
  statusInit_StandBy();
  Serial.println("3");

  // Set initial status
  status = STATUS_STAND_BY;
}

void initializePins()
{
  pinMode(DETECT_COIN_PIN, INPUT);
  pinMode(ENABLE_COIN_MACHINE_PIN, OUTPUT);
}

void loop()
{

  printStatus();

  switch (status)
  {
  case STATUS_INIT:
    break;
  default: //case "STATUS_STAND_BY":
    status = statusStandBy(status);
    break;
  }
}

void printStatus()
{
  String statusText = "STAND_BY";

  switch (status)
  {

  case STATUS_INIT:
    statusText = "INIT";
    break;
  default:
    statusText = "STAND_BY";
    break;
  }

  unsigned long timeLoop = millis();
  Serial.println("STATUS :" + statusText + " - " + timeLoop);
}
