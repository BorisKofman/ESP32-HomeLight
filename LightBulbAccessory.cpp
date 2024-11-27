#include "LightBulbAccessory.h"

// Constructor for LightBulbAccessory
LightBulbAccessory::LightBulbAccessory(int numLEDs, uint8_t maxBrightness)
  : Service::LightBulb(), numLEDs(numLEDs), maxBrightness(maxBrightness) {

  leds = new CRGB[numLEDs];
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, numLEDs); // Correct GRB order
  FastLED.setBrightness(maxBrightness);
  FastLED.clear();
  FastLED.show();

  power = new Characteristic::On();
  brightness = new Characteristic::Brightness(100);
  hue = new Characteristic::Hue(0);
  saturation = new Characteristic::Saturation(0);
}

// Destructor for LightBulbAccessory
LightBulbAccessory::~LightBulbAccessory() {
  delete[] leds;
}

// Update method called when characteristics change
boolean LightBulbAccessory::update() {
  if (power->updated()) {
    if (power->getNewVal()) {
      setLEDs();
    } else {
      FastLED.clear();
      FastLED.show();
    }
  }

  if (brightness->updated() || hue->updated() || saturation->updated()) {
    if (power->getVal()) {
      setLEDs();
    }
  }

  return true;
}

// Method to set the LEDs based on the characteristics
void LightBulbAccessory::setLEDs() {
  uint8_t mappedBrightness = map(brightness->getNewVal(), 0, 100, 0, maxBrightness);
  FastLED.setBrightness(mappedBrightness);

  float h = hue->getNewVal();              // Hue from HomeKit (0-360)
  float s = saturation->getNewVal() / 100.0; // Saturation from HomeKit (0-1)

  // Convert HSV to RGB
  CHSV hsvColor = CHSV(h * 255 / 360, s * 255, 255);
  CRGB rgbColor;
  hsv2rgb_spectrum(hsvColor, rgbColor);

  // Apply the color to all LEDs
  fill_solid(leds, numLEDs, rgbColor);
  FastLED.show();
}