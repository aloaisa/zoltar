/**
 * Waitting release coin status
 *  Wait time to release the coin with the selenoid
 *  If the button to free the coin it's pressed the selenoid is activated and free
 *  the coin. Continue with the next status.
 *  If the time pass and the button has not pressed, the coin it's free too.
 */
boolean isStatusWaittingActivateGame = false;

int freeCoin(int status) {
  digitalWrite(SOLENOID_PIN, HIGH);
  delay(SELENOID_WAIT_TIME);
  digitalWrite(SOLENOID_PIN, LOW);
    
  status = STATUS_WIN_OR_LOST;

  return status;
}

boolean isButtonPressed() {
  int inputCoin = digitalRead(FREE_COIN_BUTTON_PIN);
  if (inputCoin == HIGH) {
    return true;
  }

  return false;
}

int statusWaittingReleaseCoin(int status) { 
  if (isStatusWaittingActivateGame == false) {
    
    finishTime = millis() + FREE_COIN_TIME;
    isStatusWaittingActivateGame = true;
  }
  
  if (finishTime < millis()) {
    status = freeCoin(status);
  }

  if (isButtonPressed() == true) {
    status = freeCoin(status);
  }
  
  return status;
}

