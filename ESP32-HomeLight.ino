#include "HomeSpan.h"
#include "LightBulbAccessory.h"
#include "config.h"
#include <FastLED.h>
#include <esp_bt.h>
#include <esp_bt_main.h>

CUSTOM_CHAR(Selector, 00000001-0001-0001-0001-46637266EA00, PR+PW+EV, UINT8, 1, 1, 6, false);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Disable Bluetooth to save power
  btStop();
  esp_bt_controller_disable();

  // Initialize HomeSpan
  homeSpan.setStatusPixel(STATUS_LED_PIN, 240, 100, 5); // Configure status LED
  homeSpan.setStatusAutoOff(5);                        // Auto-off for status LED
  homeSpan.begin(Category::Bridges, "HomeLight");
  homeSpan.enableWebLog(10, "pool.ntp.org", "UTC+3");   // Web log with NTP sync
  homeSpan.setApTimeout(300);                          // Timeout for AP mode
  homeSpan.enableAutoStartAP();                        // Auto-Start AP


  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();

  // Define the Light Accessory
  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      new Characteristic::Name("HomeLight");
      new Characteristic::Model("FastLED Strip");
      new Characteristic::Manufacturer("HomeSpan");
      new Characteristic::FirmwareRevision("1.0.1");

    // Add the LightBulbAccessory service
    new LightBulbAccessory(NUM_LEDS, BRIGHTNESS);

  // Add HAP Protocol Information Service to the bridge
  new Service::HAPProtocolInformation();
    new Characteristic::Version("1.1.0");
}

void loop() {
  // Poll HomeSpan to handle HomeKit communication
  homeSpan.poll();
}