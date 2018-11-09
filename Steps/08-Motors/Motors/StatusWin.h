/**
 * Status Win:
 * Move motor with win cards
 * Stop motor when switch sensor ON and OFF again.
 */
String lastWinPosition;
boolean isStatusWinActivate;

void initStatusWin()
{
  digitalWrite(MOTOR_ENABLE_PIN, HIGH);
  digitalWrite(MOTOR_WIN_DIR_PIN, LOW);
  digitalWrite(MOTOR_WIN_STEP_PIN, LOW);
  isStatusWinActivate = false;
}

boolean moveWinCardMotor()
{
  boolean result = true;

  int input = digitalRead(SWITCH_WIN_CARD_MOTOR_PIN);
  if (input == HIGH)
  {
    lastWinPosition = "ON";
  }
  else
  {
    if (lastWinPosition == "ON")
    {
      result = false;
    }

    lastWinPosition = "OFF";
  }

  return result;
}

int statusWin(int status)
{
  if (isStatusWinActivate == false)
  {
    lastWinPosition = "OFF";
    isStatusWinActivate = true;
    digitalWrite(MOTOR_ENABLE_PIN, LOW);
  }

  if (moveWinCardMotor() == true)
  {
    Serial.println("Moving motor win cards...");

    digitalWrite(MOTOR_WIN_STEP_PIN, HIGH);
    delay(MOTOR_STEP_VELOCITY_DELAY);
    digitalWrite(MOTOR_WIN_STEP_PIN, LOW);
  }
  else
  {
    digitalWrite(MOTOR_ENABLE_PIN, HIGH);
    status = STATUS_OFF;
  }

  return status;
}