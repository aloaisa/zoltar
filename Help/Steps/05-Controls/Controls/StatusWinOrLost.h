/**
 * Status win or lost:
 * Wait a time checking the swith win and lost.
 * If sensor win ON then STATUS_WIN
 * If lostTime pass and no detect nothing then STATUS_LOST
 */
boolean isWinOrLostActivate = false;
unsigned long lostTime;
int internalStatus;

void statusWinOrLost_Reset() {
  isWinOrLostActivate = false;
}

boolean isLost() {
  return lostTime < millis();
}

void winInterrup() {
  internalStatus = STATUS_WIN;
  detachInterrupt(digitalPinToInterrupt(SENSOR_WIN_PIN));
}

int statusWinOrLost(int status) {
  if (isWinOrLostActivate == false) {
    lostTime = millis() + WAIT_LOST_TIME;
    isWinOrLostActivate = true;

    internalStatus = status;
    attachInterrupt(digitalPinToInterrupt(SENSOR_WIN_PIN), winInterrup, HIGH);
  }

  if (isLost() == true) {
    return STATUS_LOST;
  }

  return internalStatus;
}