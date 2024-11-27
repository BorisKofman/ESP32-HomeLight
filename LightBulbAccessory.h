#ifndef LIGHTBULB_ACCESSORY_H
#define LIGHTBULB_ACCESSORY_H

#include <HomeSpan.h>
#include <FastLED.h>
#include "config.h"

// Define the LightBulb accessory
struct LightBulbAccessory : Service::LightBulb {

  SpanCharacteristic *power;
  SpanCharacteristic *brightness;
  SpanCharacteristic *hue;
  SpanCharacteristic *saturation;

  CRGB *leds;
  int numLEDs;
  uint8_t maxBrightness;

  LightBulbAccessory(int numLEDs, uint8_t maxBrightness);
  ~LightBulbAccessory();
  boolean update() override;
  void setLEDs();
};

#endif // LIGHTBULB_ACCESSORY_H