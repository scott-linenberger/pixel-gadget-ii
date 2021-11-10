#include "ModeFillLight.h"

ModeFillLight::ModeFillLight(
  uint8_t (&_shapeGuageLeft)[10],
  uint8_t (&_shapeGaugeRight)[10]
) {
  shapeGaugeLeft = &_shapeGuageLeft;
  shapeGaugeRight = &_shapeGaugeRight;
}

void ModeFillLight::begin(
  Adafruit_NeoPixel &_pixels,
  Button &_btn1,
  Button &_btn2,
  Button &_btn3,
  Button &_btn4
) {
  pixels = &_pixels;

  btn1 = &_btn1;
  btn2 = &_btn2;
  btn3 = &_btn3;
  btn4 = &_btn4;

  positionCurrent = pixels->numPixels();
}

void ModeFillLight::run() {
  pixels->setPixelColor(0, pixels->Color(0, 0, 0, 120));
  pixels->show();

  while (btn1->isLongPressed()) {
    pixels->clear();
    pixels->show();

    pixels->setPixelColor(1, pixels->Color(255, 0, 0));
    pixels->show();
  }

  /* buttons */
  if (btn2->isPressed()) {
    brightnessCurrent+=brightnessIncrement;
  }

  if (btn1->isPressed()) {
    brightnessCurrent-=brightnessIncrement;
  }

  if (btn3->isPressed()) {
    positionCurrent--;
  }

  if (btn4->isPressed()) {
    positionCurrent++;
  }

  /* reset values */
  if (brightnessCurrent > brightnessMax) {
    brightnessCurrent = 0;
  }

  if (brightnessCurrent < 1) {
    brightnessCurrent = brightnessMax;
  }

  if (positionCurrent < 1) {
    positionCurrent = pixels->numPixels();
  }

  if (positionCurrent > pixels->numPixels()) {
    positionCurrent = 0;
  }

  pixels->clear();

  for (uint8_t i = 0; i < positionCurrent; i++) {
    pixels->setPixelColor(i, pixels->Color(0, 0, 0, brightnessCurrent));
  }

  pixels->show();
}