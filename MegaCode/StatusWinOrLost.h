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

  playWinSound();
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