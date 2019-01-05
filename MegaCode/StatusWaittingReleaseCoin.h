boolean isStatusWaittingActivateGame;
unsigned long waittingFinishTime;

void freeCoin() {
  Serial.println("freeCoin.");
  digitalWrite(SOLENOID_PIN, HIGH);
  Serial.println("freeCoin..");
}

void statusWaittingReleaseCoin_Reset() {
  isStatusWaittingActivateGame = false;
  // digitalWrite(SOLENOID_PIN, LOW);
}

boolean isButtonPressed() {
  int inputCoin = digitalRead(FREE_COIN_BUTTON_PIN);
  boolean result = inputCoin == LOW;

  Serial.print("isButtonPressed: ");
  Serial.println(result);

  return result;
}

int freeCoinIfGotIt(int status) {
  if (isButtonPressed() == true) {
    Serial.println("Press free coin buton!");
    freeCoin();
    // playButtonPulsedSound();
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
