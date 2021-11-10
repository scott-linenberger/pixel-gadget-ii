#include <Adafruit_NeoPixel.h>
#include "Button.h"
#include "ModeFillLight.h"

/* PIXELS */
#define LED_PIN 0
#define LED_COUNT 32
#define BRIGHTNESS 50

/* BUTTON PINS */
#define PIN_BUTTON_1 1
#define PIN_BUTTON_2 2
#define PIN_BUTTON_3 3
#define PIN_BUTTON_4 4

/* button configuration */
uint16_t TIMEOUT_PRESS = 25;
uint16_t TIMEOUT_DEBOUNCE = 25;
uint16_t TIMEOUT_LONG_PRESS = 500;
boolean STATE_BUTTON_TRIGGERED = LOW;

/* init pixels */
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

/* pixel shapes */
uint8_t shapeInfinity[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 16, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17};
uint8_t shapeGaugeLeft[] = {18, 19, 20, 21, 22, 23, 24, 25, 26, 27};
uint8_t shapeGaugeRight[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6};

/* init buttons */
Button btn1 = Button(
  PIN_BUTTON_1,
  TIMEOUT_DEBOUNCE,
  TIMEOUT_PRESS,
  TIMEOUT_LONG_PRESS,
  STATE_BUTTON_TRIGGERED);

Button btn2 = Button(
  PIN_BUTTON_2,
  TIMEOUT_DEBOUNCE,
  TIMEOUT_PRESS,
  TIMEOUT_LONG_PRESS,
  STATE_BUTTON_TRIGGERED);

Button btn3 = Button(
  PIN_BUTTON_3,
  TIMEOUT_DEBOUNCE,
  TIMEOUT_PRESS,
  TIMEOUT_LONG_PRESS,
  STATE_BUTTON_TRIGGERED);

Button btn4 = Button(
  PIN_BUTTON_4,
  TIMEOUT_DEBOUNCE,
  TIMEOUT_PRESS,
  TIMEOUT_LONG_PRESS,
  STATE_BUTTON_TRIGGERED);

/* state variables */
uint8_t modeCurr = 0;
uint8_t modeMax = 1;

/* modes */
ModeFillLight modeFillLight = ModeFillLight(
  shapeGaugeLeft,
  shapeGaugeRight
);

void setup() {
  /* init pixels */
  strip.begin();
  strip.show();
  strip.setBrightness(100);

  /* init button pins */
  pinMode(PIN_BUTTON_1, INPUT_PULLUP);
  pinMode(PIN_BUTTON_2, INPUT_PULLUP);
  pinMode(PIN_BUTTON_3, INPUT_PULLUP);
  pinMode(PIN_BUTTON_4, INPUT_PULLUP);

  modeFillLight.begin(
    strip,
    btn1,
    btn2,
    btn3,
    btn4
  );
}

void loop() {
  switch (modeCurr) {
    case 0:
      modeFillLight.run();
      break;

    default:
    break;
  }

  /* run buttons */
  btn1.run();
  btn2.run();
  btn3.run();
  btn4.run();
}
