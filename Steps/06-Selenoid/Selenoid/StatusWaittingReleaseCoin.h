/**
 * Waitting release coin status
 *  Wait time to release the coin with the selenoid
 *  If the button to free the coin it's pressed the selenoid is activated and free
 *  the coin. Continue with the next status.
 *  If the time pass and the button has not pressed, the coin it's free too.
 */
boolean isStatusWaittingActivateGame = false;
unsigned long waittingFinishTime;

void freeCoin()
{
  digitalWrite(SOLENOID_PIN, HIGH);
}

void statusWaittingReleaseCoin_Reset()
{
  isStatusWaittingActivateGame = false;
  digitalWrite(SOLENOID_PIN, LOW);
}

boolean isButtonPressed()
{
  int inputCoin = digitalRead(FREE_COIN_BUTTON_PIN);
  if (inputCoin == HIGH)
  {
    return true;
  }

  return false;
}

int freeCoinIfGotIt(int status)
{
  if (isButtonPressed() == true)
  {
    freeCoin();
    status = STATUS_WIN_OR_LOST;
  }

  if (waittingFinishTime < millis())
  {
    freeCoin();
    status = STATUS_WIN_OR_LOST;
  }

  return status;
}

int statusWaittingReleaseCoin(int status)
{
  if (isStatusWaittingActivateGame == false)
  {
    waittingFinishTime = millis() + FREE_COIN_TIME;
    isStatusWaittingActivateGame = true;
  }
  else
  {
    status = freeCoinIfGotIt(status);
  }

  return status;
}
