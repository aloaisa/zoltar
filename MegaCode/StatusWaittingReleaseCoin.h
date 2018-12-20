boolean isStatusWaittingActivateGame = false;
unsigned long waittingFinishTime;

void freeCoin() {
  digitalWrite(SOLENOID_PIN, HIGH);
}

void statusWaittingReleaseCoin_Reset() {
  isStatusWaittingActivateGame = false;
  digitalWrite(SOLENOID_PIN, LOW);
}

boolean isButtonPressed() {
  int inputCoin = digitalRead(FREE_COIN_BUTTON_PIN);
  return inputCoin == LOW;
}

int freeCoinIfGotIt(int status) {
  if (isButtonPressed() == true) {
    Serial.println("Press free coin buton!");
    freeCoin();
    playButtonPulsedSound();
    status = STATUS_WIN_OR_LOST;
  }

  if (waittingFinishTime < millis()) {
    Serial.println("Finish free coin max time!");
    freeCoin();
    playFreeSelenoidSound();
    status = STATUS_WIN_OR_LOST;
  }

  return status;
}

int statusWaittingReleaseCoin(int status) {
  if (isStatusWaittingActivateGame == false) {
    waittingFinishTime = millis() + FREE_COIN_TIME;
    isStatusWaittingActivateGame = true;
  } else {
    status = freeCoinIfGotIt(status);
  }

  return status;
}
