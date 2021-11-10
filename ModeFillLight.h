#ifndef MODE_FILL_LIGHT
#define MODE_FILL_LIGHT

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Button.h";

class ModeFillLight {

  private:
  Adafruit_NeoPixel *pixels;
  Button *btn1;
  Button *btn2;
  Button *btn3;
  Button *btn4;
  uint8_t (*shapeGaugeLeft)[10];
  uint8_t (*shapeGaugeRight)[10];
  unsigned long lastTick = 0;
  uint16_t tickWait = 10;
  uint8_t positionCurrent;
  uint8_t brightnessCurrent = 255 * 0.25;
  uint8_t brightnessMax = 255;
  uint8_t brightnessIncrement = 10;

  public:
  ModeFillLight(
    uint8_t (&_shapeGuageLeft)[10],
    uint8_t (&_shapeGaugeRight)[10]
  );
  void begin(
    Adafruit_NeoPixel &_pixels,
    Button &_btn1,
    Button &_btn2,
    Button &_btn3,
    Button &_btn4
  );
  void run();
};

#endif
