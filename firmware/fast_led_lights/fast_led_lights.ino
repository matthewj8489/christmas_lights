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

void redWipe2(CRGB * leds, int numLeds, uint32_t color)
{
  fill_solid(leds, numLeds, CRGB::Red);
}

////////////////////
// Adafruit examples
////////////////////
// turn off all leds
void allOff(CRGB * leds, int numLeds, uint32_t color) {
  FastLED.clear();
}

// R,G,B,W runs through the entire strand (best if long wait)
void christmasChase(CRGB * leds, int numLeds, uint32_t color) {
//  for(int j=0; j<4; j++) {
//    for(int q=0; q < 4; q++) {
//      for(uint16_t i=0; i<strip.numPixels(); i+=4) {
//          strip.setPixelColor(i+q, getChristmasChaseColor(j,q));
//      }
//    }
//    strip.show();
//    delay(wait);
//  }
}

uint32_t getChristmasChaseColor(int lead_clr, int on_clr) {
//  int r_val, g_val, b_val, w_val;
//  int r_num, g_num, b_num, w_num;
//
//  // color : r_val g_val b_val w_val
//  // lead  : 
//
//  if (lead_clr == 0) {
//    r_num = 0;
//    g_num = 1;
//    b_num = 2;
//    w_num = 3;
//  } else if (lead_clr == 1) {
//    r_num = 3;
//    g_num = 0;
//    b_num = 1;
//    w_num = 2;
//  } else if (lead_clr == 2) {
//    r_num = 2;
//    g_num = 3;
//    b_num = 0;
//    w_num = 1;
//  } else if (lead_clr == 3) {
//    r_num = 1;
//    g_num = 2;
//    b_num = 3;
//    w_num = 0;
//  }
//
//  r_val = (r_num==on_clr?128:0);
//  g_val = (g_num==on_clr?128:0);
//  b_val = (b_num==on_clr?128:0);
//  if (w_num == on_clr) {
//    r_val = 128;
//    g_val = 128;
//    b_val = 128;
//  }
//
//  return strip.Color(r_val, g_val, b_val);
}

// a light that has a decreasing intensity tail runs through the strip
void snakeChase(CRGB * leds, int numLeds, uint32_t color) {
//  uint32_t tail1, tail2, tail3;
//  tail1 = strip.Color(red(color)>>1, green(color)>>1, blue(color)>>1);
//  tail2 = strip.Color(red(tail1)>>1, green(tail1)>>1, blue(tail1)>>1);
//  tail2 = strip.Color(red(tail2)>>1, green(tail2)>>1, blue(tail2)>>1);
//
//  for(uint16_t i=0; i<strip.numPixels(); i++) {
//    strip.setPixelColor(i, color);
//    if (i>0) strip.setPixelColor(i-1, tail1);
//    if (i>1) strip.setPixelColor(i-2, tail2);
//    if (i>2) strip.setPixelColor(i-3, tail3);
//    if (i>3) strip.setPixelColor(i-4, strip.Color(0,0,0));
//    strip.show();
//    delay(wait);
//  }
//
//  // set all the pixels to black
//  strip.setPixelColor(strip.numPixels() - 1, strip.Color(0,0,0));
//  strip.setPixelColor(strip.numPixels() - 2, strip.Color(0,0,0));
//  strip.setPixelColor(strip.numPixels() - 3, strip.Color(0,0,0));
//  strip.setPixelColor(strip.numPixels() - 4, strip.Color(0,0,0));
}

//int currentSlowPulseColor=RED_PULSE;
void slowPulseCycle(uint8_t intensity_low, uint8_t intensity_high, uint8_t wait) {
//  slowPulse(currentSlowPulseColor, intensity_low, intensity_high, wait);
//  currentSlowPulseColor++;
//  if (currentSlowPulseColor > WHITE_PULSE)
//    currentSlowPulseColor=RED_PULSE;
}

// color : 0 = r, 1 = g, 2 = b, 3 = w
void slowPulse(uint8_t color, uint8_t intensity_low, uint8_t intensity_high, uint8_t wait) {
//  for(uint32_t i=intensity_low; i<=intensity_high; i++) {
//    for(uint16_t j=0; j<strip.numPixels(); j++) {
//      switch(color) {
//        case RED_PULSE:
//          strip.setPixelColor(j, strip.Color(i, 0, 0));
//          break;
//        case GREEN_PULSE:
//          strip.setPixelColor(j, strip.Color(0, i, 0));
//          break;
//        case BLUE_PULSE:
//          strip.setPixelColor(j, strip.Color(0, 0, i));
//          break;
//        default:
//          strip.setPixelColor(j, strip.Color(i, i, i));
//      }
//      //strip.setPixelColor(j, i);
//    }
//    strip.show();
//    delay(wait);
//  }
//
//  for(int32_t i=intensity_high; i>=intensity_low; i--) {
//    for (uint16_t j=0; j<strip.numPixels(); j++) {
//      switch(color) {
//        case RED_PULSE:
//          strip.setPixelColor(j, strip.Color(i, 0, 0));
//          break;
//        case GREEN_PULSE:
//          strip.setPixelColor(j, strip.Color(0, i, 0));
//          break;
//        case BLUE_PULSE:
//          strip.setPixelColor(j, strip.Color(0, 0, i));
//          break;
//        default:
//          strip.setPixelColor(j, strip.Color(i, i, i));
//      }
//      //strip.setPixelColor(j, i);
//    }
//    strip.show();
//    delay(wait);
//  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
//  for(uint16_t i=0; i<strip.numPixels(); i++) {
//    strip.setPixelColor(i, c);
//    strip.show();
//    delay(wait);
//  }
}

// color runs along the led strip and back
void colorChase(uint32_t c, uint8_t wait) {
//  for(uint16_t i=0; i<strip.numPixels(); i++) {
//    strip.setPixelColor(i, c);
//    if (i>0)
//      strip.setPixelColor(i-1,0);
//    strip.show();
//    delay(wait);
//  }
//
//  for(int16_t i=strip.numPixels()-1; i>=0; i--) {
//    strip.setPixelColor(i, c);
//    if (i<strip.numPixels()-1)
//      strip.setPixelColor(i+1, 0);
//    strip.show();
//    delay(wait);
//  }
//
//  strip.setPixelColor(0, 0);
//  strip.show();
//  delay(wait);
}

//void rainbow(uint8_t wait) {
//  uint16_t i, j;
//
//  for(j=0; j<256; j++) {
//    for(i=0; i<strip.numPixels(); i++) {
//      strip.setPixelColor(i, Wheel((i+j) & 255));
//    }
//    strip.show();
//    delay(wait);
//  }
//}

// Slightly different, this makes the rainbow equally distributed throughout
//void rainbowCycle(uint8_t wait) {
//  uint16_t i, j;
//
//  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
//    for(i=0; i< strip.numPixels(); i++) {
//      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
//    }
//    strip.show();
//    delay(wait);
//  }
//}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
//  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
//    for (int q=0; q < 3; q++) {
//      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
//        strip.setPixelColor(i+q, c);    //turn every third pixel on
//      }
//      strip.show();
//
//      delay(wait);
//
//      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
//        strip.setPixelColor(i+q, 0);        //turn every third pixel off
//      }
//    }
//  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
//  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
//    for (int q=0; q < 3; q++) {
//      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
//        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
//      }
//      strip.show();
//
//      delay(wait);
//
//      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
//        strip.setPixelColor(i+q, 0);        //turn every third pixel off
//      }
//    }
//  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
//  WheelPos = 255 - WheelPos;
//  if(WheelPos < 85) {
//    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  }
//  if(WheelPos < 170) {
//    WheelPos -= 85;
//    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  }
//  WheelPos -= 170;
//  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// 0 - 127
uint32_t WheelHalfIntensity(byte WheelPos) {
//  WheelPos = 127 - WheelPos;
//  if(WheelPos < 42) {
//    return strip.Color(127 - WheelPos * 3, 0, WheelPos * 3);
//  }
//  if(WheelPos < 85) {
//    WheelPos -= 42;
//    return strip.Color(0, WheelPos * 3, 127 - WheelPos * 3);
//  }
//  WheelPos -= 85;
//  return strip.Color(WheelPos * 3, 127 - WheelPos * 3, 0);
}

uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}

///////////////////////////
// FastLED example patterns
///////////////////////////
void rainbow(CRGB * leds, int numLeds, uint32_t color) 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, numLeds, color, 7);
}

void rainbowWithGlitter(CRGB * leds, int numLeds, uint32_t color) 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow(leds, numLeds, color);
  addGlitter(80, leds, numLeds);
}

void addGlitter( fract8 chanceOfGlitter, CRGB * leds, int numLeds) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(numLeds) ] += CRGB::White;
  }
}

void confetti(CRGB * leds, int numLeds, uint32_t color) 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, numLeds, 10);
  int pos = random16(numLeds);
  leds[pos] += CHSV( color + random8(64), 200, 255);
}

void sinelon(CRGB * leds, int numLeds, uint32_t color)
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, numLeds, 20);
  int pos = beatsin16( 13, 0, numLeds-1 );
  leds[pos] += CHSV( color, 255, 192);
}

void bpm(CRGB * leds, int numLeds, uint32_t color)
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < numLeds; i++) { //9948
    leds[i] = ColorFromPalette(palette, color+(i*2), beat-color+(i*10));
  }
}

void juggle(CRGB * leds, int numLeds, uint32_t color) {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, numLeds, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, numLeds-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}


/************************************/

#define NUM_LEDS 100

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
//long debouncing_time = 20; //debounce time in ms
#define DEBOUNCE_TIME 20
volatile unsigned long last_micros = 0;

// List of patterns to display
typedef void (*PatternList[])(CRGB*,int,uint32_t);
PatternList mPatterns = {rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm};
uint32_t mPatternArraySize;
uint8_t mCurrentPattern = 0;


// Helpful macros/functions
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

#define POT_BRIGHT  0
#define POT_PATTERN 1
#define POT_COLOR   2
uint8_t mPotState = POT_PATTERN;
#define POT_STATES  3

uint8_t mHue = 0;

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

  pinMode(SWITCH_PIN, INPUT);
	attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), debounceInterrupt, FALLING);
}

//uint8_t mClearLeds = 1;

void loop()
{
  int switchState = digitalRead(SWITCH_PIN);
  
  //if (mClearLeds == 1)
  //{
  //  FastLED.clear();
  //}
  //else
  //{
  //	// Make adjustment to the leds
  //  if (mPatterns[mCurrentPattern](leds, NUM_LEDS, gHue) == PATTERN_FINISHED)
  //    mClearLeds = 1;
  //} 

  if (switchState == 1)
  {
    mPatterns[mCurrentPattern](leds, NUM_LEDS, mHue);
      
  	// Show the changes
  	FastLED.show();
   
  	// Delay
    FastLED.delay(1000/FRAMES_PER_SECOND);
  
    // Read the pot dial and change which pattern is displayed
    //int idx;
    //idx = patternIndex(analogRead(POT_PIN));
    //if (mCurrentPattern != idx)
    //{
    //  mClearLeds = 1;
    //  mCurrentPattern = idx;
    //}

    // Check the potentiometer
    switch(mPotState)
    {
      case POT_BRIGHT:
        changeBrightness(analogRead(POT_PIN));
        break;
      case POT_PATTERN:
        changePattern(analogRead(POT_PIN));
        break;
      case POT_COLOR:
        changeBaseColor(analogRead(POT_PIN));
        break;
    }
    //mCurrentPattern = patternIndex(analogRead(POT_PIN));

    EVERY_N_MILLISECONDS( 20 ) { mHue++; }
  }
  else
  {
    FastLED.clear();

    FastLED.delay(1000/FRAMES_PER_SECOND);
  }
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= DEBOUNCE_TIME * 1000){
	  // change state of the button here
	  //mCurrentPattern = (mCurrentPattern + 1) % mPatternArraySize;
    //mClearLeds = 1;
    mPotState = (mPotState + 1) % POT_STATES;
  
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

uint16_t currentBrightness = BRIGHTNESS;
void changeBrightness(uint16_t pot_val)
{
  uint8_t brt;
  brt = (pot_val * 255) / 1023;
  if (currentBrightness != brt)
  {
    FastLED.setBrightness(brt);
    currentBrightness = brt;  
  }  
}

void changePattern(uint16_t pot_val)
{
  mCurrentPattern = patternIndex(pot_val);
}

void changeBaseColor(uint16_t pot_val)
{
  uint16_t clr;
  clr = (pot_val * 255) / 1023;
  mHue = clr;
}

