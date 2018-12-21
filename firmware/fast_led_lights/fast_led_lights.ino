#include <FastLED.h>

/********** Color Patterns **********/
#define PATTERN_FINISHED  0
uint16_t led_idx = 0; 
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

uint16_t ccLedIdx = 0;
int8_t dir = 1;
/*
 * colorChase
 * 
 * Color runs along the led strip and back
 */
uint8_t colorChase(CRGB * leds, int numLeds, uint32_t color)
{
  leds[ccLedIdx] = color;
  if (ccLedIdx - 1 >= 0)
    leds[ccLedIdx-1] = 0;

  ccLedIdx+=dir;
  if (ccLedIdx == numLeds)
  {
    dir = -1;
    return ~PATTERN_FINISHED;  
  }
  else if (ccLedIdx == 0)
  {
    dir = 1;
    return PATTERN_FINISHED;
  }
  else
  {
    return ~PATTERN_FINISHED;
  }
}

////////////////////////
// different methodology
////////////////////////
void redWipe(CRGB * leds, int numLeds)
{
  uint16_t num;
  num = lerp16by8(0, numLeds-1, 0);
  fill_solid(leds, num, CRGB::Red);
}


/************************************/

#define NUM_LEDS 100

#define DATA_PIN 6


#define BUTTON_PIN	2	// Digital IO pin connected to the button.  This will be
                        // driven with a pull-up resistor so the switch should
                        // pull the pin to ground momentarily.  On a high -> low
                        // transition the button press logic will execute. 

#define POT_PIN A1 // Analog pin 1 is used for the potentiometer voltage
                      // reading.
                      
			
// Create a data array of all the available LEDs			
CRGB leds[NUM_LEDS];

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


#define BRIGHTNESS 128
#define FRAMES_PER_SECOND 120


// Debounce tracking
long debouncing_time = 15; //debounce time in ms
volatile unsigned long last_micros = 0;


// List of patterns to display
typedef uint8_t (*PatternList[])(CRGB*,int,uint32_t);
PatternList mPatterns = {colorWipe};
uint32_t mPatternArraySize;
uint8_t mCurrentPattern = 0;


// Helpful macros/functions
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


void setup()
{
	delay( 3000 ); // power-up safety delay
	
	// Uncomment/edit one of the following lines for your leds arrangement.
	// FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	// FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);

	// FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);

	// FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	// FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
	
	FastLED.setBrightness(BRIGHTNESS);

  mPatternArraySize = ARRAY_SIZE(mPatterns);
  
	attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), debounceInterrupt, FALLING);
}

uint8_t mClearLeds = 1;

void loop()
{
  if (mClearLeds == 1)
  {
    FastLED.clear();
  }
  else
  {
  	// Make adjustment to the leds
    if (mPatterns[mCurrentPattern](leds, NUM_LEDS, 0x00AA00) == PATTERN_FINISHED)
      mClearLeds = 1;
  } 
  
	// Show the changes
	FastLED.show();
 
	// Delay
  FastLED.delay(1000/FRAMES_PER_SECOND);

  // Read the pot dial and change which pattern is displayed
  int idx;
  idx = patternIndex(analogRead(POT_PIN));
  if (mCurrentPattern != idx)
  {
    mClearLeds = 1;
    mCurrentPattern = idx;
  }
  
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000){
	  // change state of the button here
	  mCurrentPattern = (mCurrentPattern + 1) % mPatternArraySize;
    mClearLeds = 1;
  
	  // reset the debounce
    last_micros = micros();
  }
}

// A pattern is associated to each division of a pot value
uint8_t patternIndex(int pot_val)
{
  //return map(pot_val, 0, 1023, 0, mPatternArraySize - 1);  
  return ((pot_val * mPatternArraySize) / 1023);
}
