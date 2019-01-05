boolean isWinOrLostActivate;
unsigned long lostTime;
volatile int internalStatus;

void statusWinOrLost_Reset() {
  isWinOrLostActivate = false;
}

boolean isLost() {
  return lostTime < millis();
}

void winInterrup() {
  Serial.println("winInterrup.");
  internalStatus = STATUS_WIN;
}

int statusWinOrLost(int status) {
  if (isWinOrLostActivate == false) {
    lostTime = millis() + WAIT_LOST_TIME;
    isWinOrLostActivate = true;

    internalStatus = status;
    attachInterrupt(digitalPinToInterrupt(SENSOR_WIN_PIN), winInterrup, RISING);
  }

  if (isLost() == true) {
    Serial.println("isLost.");
    internalStatus = STATUS_LOST;
  }

  return internalStatus;
}