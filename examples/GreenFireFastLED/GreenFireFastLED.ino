/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

 /*
  * An example for the Arduino particle system library
  * Creates a green fire effect
  */

#include <SmartMatrix.h>
#include <FastLED.h>
#include <ParticleSys.h>

#define LED_WIDTH 32
#define LED_HEIGHT 32

// set ledSerpentineLayout to true if your matrix looks wrong ;) - see Example "XYMatrix" in FastLED library.
const bool ledSerpentineLayout = false;  
// translates from x, y into an index into the LED array
uint16_t XY( uint8_t x, uint8_t y) {
  if(y >= LED_HEIGHT) { y = LED_HEIGHT - 1; }
  if(x >= LED_WIDTH) { x = LED_WIDTH - 1; }
  uint16_t ret;
  if(ledSerpentineLayout == false) {
    ret = (y * LED_WIDTH) + x;
  } else {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t revX = (LED_WIDTH - 1) - x;
      ret = (y * LED_WIDTH) + revX;
    } else {
      // Even rows run forwards
      ret = (y * LED_WIDTH) + x;
    }
  }
  return ret;
}

#define NUM_LEDS    (LED_WIDTH * LED_HEIGHT)
//#define LED_PIN     7
//#define COLOR_ORDER GRB
#define CHIPSET     SMART_MATRIX
#define BRIGHTNESS  255
CRGB leds[ NUM_LEDS ];

const byte numParticles = 60;

ParticleSysConfig g(LED_WIDTH, LED_HEIGHT);
Particle_Std particles[numParticles];
Emitter_Fire emitter;
ParticleSys pSys(&g, numParticles, particles, &emitter);
FastLEDRenderer renderer(&g);

void setup() {
  FastLED.addLeds<CHIPSET>(leds, NUM_LEDS);
  FastLED.setBrightness( BRIGHTNESS );

  randomSeed(analogRead(0));
  
  renderer.reset(leds);
  
  Particle_Std::ay = -1;
  pSys.perCycle = 10;
  emitter.baseHue = 75; // green
  // emitter.baseHue = 156; // blue
  emitter.maxTtl = 96;
  
}

void loop() {
    pSys.update();
    renderer.reset(leds);
    renderer.render(&g, particles, numParticles, leds);
    FastLED.show();
    delay(8);
}

