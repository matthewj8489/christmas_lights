//#include <bitswap.h>
//#include <chipsets.h>
//#include <color.h>
//#include <colorpalettes.h>
//#include <colorutils.h>
//#include <controller.h>
//#include <cpp_compat.h>
//#include <dmx.h>
#include <FastLED.h>
//#include <fastled_config.h>
//#include <fastled_delay.h>
//#include <fastled_progmem.h>
//#include <fastpin.h>
//#include <fastspi.h>
//#include <fastspi_bitbang.h>
//#include <fastspi_dma.h>
//#include <fastspi_nop.h>
//#include <fastspi_ref.h>
//#include <fastspi_types.h>
//#include <hsv2rgb.h>
//#include <led_sysdefs.h>
//#include <lib8tion.h>
//#include <noise.h>
//#include <pixelset.h>
//#include <pixeltypes.h>
//#include <platforms.h>
//#include <power_mgt.h>

#include <EEPROM.h>

#define NUM_LEDS 100
#define CANDLE_LENGTH   NUM_LEDS / 4
#define CANDLE_1_START  NUM_LEDS * 3 / 4
#define CANDLE_2_START  0
#define CANDLE_3_START  NUM_LEDS / 4
#define CANDLE_4_START  NUM_LEDS / 2

#define DATA_PIN 6


#define BUTTON_PIN	2	// Digital IO pin connected to the button.  This will be
                      //   driven with a pull-up resistor so the switch should
                      //   pull the pin to ground momentarily.  On a high -> low
                      //   transition the button press logic will execute. 
      
			
// Create a data array of all the available LEDs			
CRGB leds[NUM_LEDS];

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


#define BRIGHTNESS 128
#define FRAMES_PER_SECOND 120


// Debounce tracking
#define DEBOUNCE_TIME 500
volatile unsigned long last_millis = 0;

typedef enum candles_lit
{
    candles_0 = 0,
    candles_1 = 1,
    candles_2 = 2,
    candles_3 = 3,
    candles_4 = 4
} CANDLES_LIT;
CANDLES_LIT mCurrentCandlesLitState = candles_0;
CANDLES_LIT mNewCandlesLitState = candles_0;

#define HUE_PURPLE  140//purple:138//less blue:148//blue:156
#define HUE_PINK    118//pink:128
#define VAL_ON_PURPLE 200
#define VAL_ON      255
#define VAL_DIM     64

#define EFFECT_DELAY  100

// Helpful macros/functions
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


// Effects
void effect_pixel_fade(CRGB * leds, int numLeds, uint8_t hue_color, int pix, uint8_t val = 255)
{
  leds[pix] = CHSV(hue_color, 255, val);
  val -= 1;

  FastLED.show();

  FastLED.delay(EFFECT_DELAY);

  if (val <= 0)
    return;
  else
    return effect_pixel_fade(leds, numLeds, hue_color, pix, val);
}


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
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
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

  Serial.begin(9600);

  mCurrentCandlesLitState = EEPROM.read(0);

  if (mCurrentCandlesLitState != candles_0 && mCurrentCandlesLitState != candles_1 && mCurrentCandlesLitState != candles_2 && mCurrentCandlesLitState != candles_3 && mCurrentCandlesLitState != candles_4)
    mCurrentCandlesLitState = candles_0;
    
}

void loop()
{
    // Change which LEDs are on
    if (mCurrentCandlesLitState != mNewCandlesLitState)
    {
        mCurrentCandlesLitState = mNewCandlesLitState;
        EEPROM.write(0, mCurrentCandlesLitState);

        if(mCurrentCandlesLitState == candles_1 || mCurrentCandlesLitState == candles_2 || mCurrentCandlesLitState == candles_3 || mCurrentCandlesLitState == candles_4)
            fill_solid(&leds[CANDLE_1_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_ON_PURPLE));
        else
            fill_solid(&leds[CANDLE_1_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_DIM));

        if(mCurrentCandlesLitState == candles_2 || mCurrentCandlesLitState == candles_3 || mCurrentCandlesLitState == candles_4)
            fill_solid(&leds[CANDLE_2_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_ON_PURPLE));
        else
            fill_solid(&leds[CANDLE_2_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_DIM));

        if(mCurrentCandlesLitState == candles_3 || mCurrentCandlesLitState == candles_4)
            fill_solid(&leds[CANDLE_3_START], CANDLE_LENGTH, CHSV(HUE_PINK, 255, VAL_ON));
        else
            fill_solid(&leds[CANDLE_3_START], CANDLE_LENGTH, CHSV(HUE_PINK, 255, VAL_DIM));

        if(mCurrentCandlesLitState == candles_4)
            fill_solid(&leds[CANDLE_4_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_ON_PURPLE));
        else
            fill_solid(&leds[CANDLE_4_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_DIM));
    }

    // Run through the flicker algorithm
    //if(mCurrentCandlesLitState == candles_1 || mCurrentCandlesLitState == candles_2 || mCurrentCandlesLitState == candles_3 || mCurrentCandlesLitState == candles_4)
    //    effect_pixel_fade(&leds[CANDLE_1_START], CANDLE_LENGTH, HUE_PURPLE, random(CANDLE_LENGTH));
    //if(mCurrentCandlesLitState == candles_2 || mCurrentCandlesLitState == candles_3 || mCurrentCandlesLitState == candles_4)
    //    effect_pixel_fade(&leds[CANDLE_2_START], CANDLE_LENGTH, HUE_PURPLE, random(CANDLE_LENGTH));
    //if(mCurrentCandlesLitState == candles_3 || mCurrentCandlesLitState == candles_4)
    //    effect_pixel_fade(&leds[CANDLE_3_START], CANDLE_LENGTH, HUE_PINK, random(CANDLE_LENGTH));
    //if(mCurrentCandlesLitState == candles_4)
    //    effect_pixel_fade(&leds[CANDLE_4_START], CANDLE_LENGTH, HUE_PURPLE, random(CANDLE_LENGTH));

    FastLED.delay(EFFECT_DELAY);
        
    // Show the changes
    //FastLED.show();

    // Delay
    //FastLED.delay(1000/FRAMES_PER_SECOND);

    //EVERY_N_SECONDS( 10 ) { mCurrentPattern = (mCurrentPattern + 1) % mPatternArraySize; }
    //EVERY_N_MILLISECONDS( 20 ) { mHue++; }
}

void debounceInterrupt() {
  if((long)(millis() - last_millis) >= DEBOUNCE_TIME){
    // change state of the button here
    mNewCandlesLitState = (mNewCandlesLitState <= candles_4) ? mNewCandlesLitState + 1 : candles_0;

    // reset the debounce
    last_millis = millis();
  }
}
