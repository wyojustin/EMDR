/*
 * USB animation server based on
 *   ESP8266 + FastLED + IR Remote: https://github.com/jasoncoon/esp8266-fastled-webserver
 *   Copyright (C) 2015-2016 Jason Coon
 * Ported by Justin Shaw
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <FastLED.h>
#include "MatrixMap.h"

FASTLED_USING_NAMESPACE

#define DATA_PIN      MOSI
#define CLK_PIN       SCK
#define LED_TYPE      APA102
#define COLOR_ORDER   BGR

#define MILLI_AMPS         2000     // IMPORTANT: set the max milli-Amps of your power supply (4A = 4000mA)

CRGB leds[NUM_LEDS];

CRGB solidColor = CRGB::Blue;
uint8_t brightness = 32;

void setup() {
  Serial.begin(115200);
  delay(100);

  FastLED.addLeds<LED_TYPE, DATA_PIN, CLK_PIN, COLOR_ORDER>(leds, NUM_LEDS); // for APA102 (Dotstar)
  FastLED.setDither(false);
  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, MILLI_AMPS);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void loop() {
  EMDR();
  FastLED.show();
}

void EMDR(){
  FastLED.clear();

  static uint8_t x = 0;
  static uint8_t y = 3;
  static uint8_t dir = 1;
  static uint32_t last_ms = 0;
  
  leds[XY(x, y)] = solidColor;
  leds[XY(x+1, y)] = solidColor;
  leds[XY(x+1, y+1)] = solidColor;
  leds[XY(x, y+1)] = solidColor;

  x = x + dir;
  if (x >= MatrixWidth) {
    x = MatrixWidth - 3;
    dir = -1;
  }
  if(x <= 0){
    x = 0;
    dir = 1;
  }
}
