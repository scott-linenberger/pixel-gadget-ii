#include "Button.h"
#include <Arduino.h>

/* constructor */
Button::Button(
  uint8_t _pin,
  uint16_t _timeoutDebounce,
  uint16_t _timeoutDepressed,
  uint16_t _timeoutLongPress,
  boolean _triggeredState
) {
  /* assign vars */
  pin = _pin;
  timeoutDebounce = _timeoutDebounce;
  timeoutDepressed = _timeoutDepressed;
  timeoutLongPress = _timeoutLongPress;
  triggeredState = _triggeredState;

  /** Add the timeout period to the last pressed timestamp.
   * This prevents the button from being locked out on start */
  timeLastTriggered = millis() + timeoutDebounce;
}

boolean Button::isTimeoutExpired() {
  return (millis() - timeLastTriggered >= timeoutDebounce);
}

void Button::begin() {
  /* default begin method */
}

void Button::run() {
  if (digitalRead(pin) != triggeredState) {
    timeLongPressTriggered = millis();
  }
}

boolean Button::isLongPressed() {
  /* button isn't pressed, not triggered */
  if (digitalRead(pin) != triggeredState) {
    return false;
  }

  /* check if the debounce period has expired */
  if ((millis() - timeLastTriggered) < timeoutDebounce) {
    return false;
  }

  /* debounce has expired */
  /* wait to see if the button is held long enough */
  if ((millis() - timeLongPressTriggered) >= timeoutLongPress) {
    return true;
  }

  return false;
}

boolean Button::isPressed() {
  /* button isn't pressed, not triggered */
  if (digitalRead(pin) != triggeredState) {
    return false;
  }

  /* check if the debounce period has expired */
  if ((millis() - timeLastTriggered) < timeoutDebounce) {
    return false;
  }

  /* pressed! */
  unsigned long timeTriggered = millis();

  /* debounce has expired */
  /* wait to see if the button is held long enough */
  while ((millis() - timeTriggered) < timeoutDepressed) {
    if (digitalRead(pin) != triggeredState) {
      /* button released too soon! */
      return false;
    }
  }

  /* button was held down long enough, but is it held down too long? */
  /* could be attempting a long-press */
  while (digitalRead(pin) == triggeredState) {
    if ((millis() - timeTriggered) >= timeoutLongPress) {
      /* held down longer than a long press */
      /* start steadily showing presses */
      /* reset time last triggered */
      timeLastTriggered = millis();
      return true;   }
  }

  /* don't send one last "pressed" after long pressing */
  if ((millis() - timeTriggered) >= timeoutLongPress) {
    return false;
  }

  /* reset time last triggered */
  timeLastTriggered = millis();
  return true;
}