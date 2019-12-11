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

#define SWITCH_PIN  4 // Digitla IO pin connected to the switch. The switch 
                      //   turns the LEDs on/off

#define POT_PIN A1 // Analog pin 1 is used for the potentiometer voltage
                   //   reading.
                      
			
// Create a data array of all the available LEDs			
CRGB leds[NUM_LEDS];

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


#define BRIGHTNESS 128
#define FRAMES_PER_SECOND 120


// Debounce tracking
#define DEBOUNCE_TIME 20
volatile unsigned long last_micros = 0;

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

#define COLOR_PURPLE        0x6a0dad
#define COLOR_DIM_PURPLE    0x350656 // 1/2 intensity; 0x1a032b // 1/4 intensity
#define COLOR_PINK          0xffc0cb
#define COLOR_DIM_PINK      0x7f6065 // 1/2 intensity; 0x3f3032 // 1/4 intensity

#define HUE_PURPLE  192
#define HUE_PINK    224
#define VAL_ON      255
#define VAL_DIM     64

// Helpful macros/functions
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


// Effects
void effect_flicker(CRGB * leds, int numLeds, uint32_t color)
{

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

  mPatternArraySize = ARRAY_SIZE(mPatterns);

  pinMode(SWITCH_PIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), debounceInterrupt, FALLING);

  Serial.begin(9600);
}

void loop()
{
    // Change which LEDs are on
    if (mCurrentCandlesLitState != mNewCandlesLitState)
    {
        mCurrentCandlesLitState = mNewCandlesLitState;

        if(mCurrentCandlesLitState == candles_1)
            fill_solid(&leds[CANDLE_1_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_ON));
        else
            fill_solid(&leds[CANDLE_1_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_DIM));

        if(mCurrentCandlesLitState == candles_2)
            fill_solid(&leds[CANDLE_2_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_ON));
        else
            fill_solid(&leds[CANDLE_2_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_DIM));

        if(mCurrentCandlesLitState == candles_3)
            fill_solid(&leds[CANDLE_3_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_ON));
        else
            fill_solid(&leds[CANDLE_3_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_DIM));

        if(mCurrentCandlesLitState == candles_4)
            fill_solid(&leds[CANDLE_4_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_ON));
        else
            fill_solid(&leds[CANDLE_4_START], CANDLE_LENGTH, CHSV(HUE_PURPLE, 255, VAL_DIM));
    }

    // Run through the flicker algorithm
    if(mCurrentCandlesLitState == candles_1)
        effect_flicker(&leds[CANDLE_1_START], CANDLE_LENGTH, COLOR_PURPLE);
    if(mCurrentCandlesLitState == candles_2)
        effect_flicker(&leds[CANDLE_2_START], CANDLE_LENGTH, COLOR_PURPLE);
    if(mCurrentCandlesLitState == candles_3)
        effect_flicker(&leds[CANDLE_3_START], CANDLE_LENGTH, COLOR_PURPLE);
    if(mCurrentCandlesLitState == candles_4)
        effect_flicker(&leds[CANDLE_4_START], CANDLE_LENGTH, COLOR_PURPLE);
        
    // Show the changes
    FastLED.show();

    // Delay
    FastLED.delay(1000/FRAMES_PER_SECOND);

    //EVERY_N_SECONDS( 10 ) { mCurrentPattern = (mCurrentPattern + 1) % mPatternArraySize; }
    //EVERY_N_MILLISECONDS( 20 ) { mHue++; }
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= DEBOUNCE_TIME * 1000){
    // change state of the button here
    mNewCandlesLitState = (mNewCandlesLitState <= candles_4) ? mNewCandlesLitState + 1 : candles_0;

    // reset the debounce
    last_micros = micros();
  }
}
