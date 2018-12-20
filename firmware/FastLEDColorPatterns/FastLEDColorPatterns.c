
#include "FastLEDColorPatterns.h"


uint8_t led_idx = 0; 
uint8_t colorWipe(CRGB * leds, int numLeds, uint32_t color)
{
	leds[led_idx++] = color;
	if (led_idx == numLeds)
	{
		led_idx = 0;
		return PATTERN_FINISHED;
	}
	else
		return ~PATTERN_FINISHED;
}


