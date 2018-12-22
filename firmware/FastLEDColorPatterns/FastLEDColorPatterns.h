#ifndef FASTLEDCOLORPATTERNS_H
#define FASTLEDCOLORPATTERNS_H


#include <FastLED.h>

#define PATTERN_FINISHED	0

// pattern prototype:
// uint8_t pattern(CRGB*, int, uint32_t)


uint8_t colorWipe(CRGB * leds, int numLeds, uint32_t color);












#endif //FASTLEDCOLORPATTERNS_H