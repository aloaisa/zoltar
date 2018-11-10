/**
 * Status win or lost:
 * Wait a time checking the swith win and lost.
 * If sensor win ON then STATUS_WIN
 * If lostTime pass and no detect nothing then STATUS_LOST
 */
boolean isWinOrLostActivate = false;
unsigned long lostTime;

void statusWinOrLost_Reset()
{
  isWinOrLostActivate = false;
}

boolean isWin()
{
  int input = digitalRead(SENSOR_WIN_PIN);
  return input == HIGH;
}

boolean isLost()
{
  return lostTime < millis();
}

int statusWinOrLost(int status)
{
  if (isWinOrLostActivate == false)
  {
    lostTime = millis() + WAIT_LOST_TIME;
    isWinOrLostActivate = true;
  }

  if (isWin() == true)
  {
    return STATUS_WIN;
  }
  else if (isLost() == true)
  {
    return STATUS_LOST;
  }

  return status;
}