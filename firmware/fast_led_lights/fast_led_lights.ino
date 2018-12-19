#include <FastLED.h>

#define NUM_LEDS 100

#define DATA_PIN 6


#define BUTTON_PIN	2	// Digital IO pin connected to the button.  This will be
                        // driven with a pull-up resistor so the switch should
                        // pull the pin to ground momentarily.  On a high -> low
                        // transition the button press logic will execute. 
			
			
// Create a data array of all the available LEDs			
CRGB leds[NUM_LEDS];

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


#define BRIGHTNESS 128


// Debounce tracking
long debouncing_time = 15; //debounce time in ms
volatile unsigned long last_micros = 0;


// Pattern prototypes
uint8_t colorWipe(CRGB * leds, int numLeds, uint32_t color);

// List of patterns to display
typedef uint8_t (*PatternList[])(CRGB*,int,uint32_t);
PatternList mPatterns = {colorWipe};

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
	
	attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), debounceInterrupt, FALLING);
}


void loop()
{
	// Make adjustment to the leds
  if (mPatterns[mCurrentPattern](leds, NUM_LEDS, 0x00AA00) == PATTERN_FINISHED)
    mCurrentPattern = (mCurrentPattern + 1) % ARRAY_SIZE(mPatterns);
    
	// Show the changes
	FastLED.show();
 
	// Delay
  FastLED.delay(10);
	
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000){
    
	// change state of the button here
	
	// reset the debounce
    last_micros = micros();
  }
}


/** Color Patterns **/

#define PATTERN_FINISHED  0
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
