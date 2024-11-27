// config.h
#ifndef CONFIG_H
#define CONFIG_H

// Pin Definitions
#define LED_PIN 14 // Pin for addressable LEDs (WS2812, SK6812, etc.)
#define STATUS_LED_PIN 48 // Pin for the status LED

// LED Settings
#define NUM_LEDS 13 // Number of LEDs in the strip
#define BRIGHTNESS 100 // Default brightness percentage

// FastLED LED array
extern CRGB leds[NUM_LEDS];

#endif // CONFIG_H