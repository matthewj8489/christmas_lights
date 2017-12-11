#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define BUTTON_PIN   2    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute. 

#define PIXEL_PIN 6

#define PIXEL_COUNT 100

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_RGB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

#define RED_PULSE 0
#define GREEN_PULSE 1
#define BLUE_PULSE 2
#define WHITE_PULSE 3

#define MAX_SHOWS 10

//bool oldState = HIGH;
int showType = 0;

long debouncing_time = 15; //debounce time in ms
volatile unsigned long last_micros = 0;

void setup() {
  // put your setup code here, to run once:
  //pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), debounceInterrupt, FALLING);
  strip.begin();
  strip.show();

  colorWipe(strip.Color(0, 0, 0), 50);
}

void loop() {

  //colorWipe(strip.Color(64, 0, 0), 50);
  //colorWipe(strip.Color(0, 64, 0), 50);
  //colorWipe(strip.Color(0, 0, 64), 50);

  // all leds blinking at different times (same color)
  //theaterChase(strip.Color(0, 127, 0), 50);

  // smoothly transitioning between colors
  //rainbow(20);

  // same as rainbow, except the colors move down the pixel line
  //rainbowCycle(20);

  // theaterChase + rainbow
  //theaterChaseRainbow(50);
  
  //slowPulse(RED_PULSE, 10, 127, 50);
  //slowPulse(GREEN_PULSE, 1, 127, 20);
  //slowPulse(BLUE_PULSE, 10, 127, 50);
  //slowPulse(WHITE_PULSE, 10, 127, 50);

  //colorChase(strip.Color(127, 0, 127), 150);

  //snakeChase(strip.Color(127, 0, 0), 100);



    // Get current button state.
//  bool newState = digitalRead(BUTTON_PIN);
//
//  // Check if state changed from high to low (button press).
//  if (newState == LOW && oldState == HIGH) {
//    // Short delay to debounce button.
//    delay(20);
//    // Check if button is still low after debounce.
//    newState = digitalRead(BUTTON_PIN);
//    if (newState == LOW) {
//      showType++;
//      if (showType > 9)
//        showType=0;
//      startShow(showType);
//    }
//  }
//
//  // Set the last button state to the old state.
//  oldState = newState;

  startShow(showType);
  
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000){
    showType++;
    if (showType > MAX_SHOWS) showType=0;
    last_micros = micros();
  }
}

void startShow(int i) {
  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
            break;
    case 1: colorWipe(strip.Color(64, 0, 0), 50);  // Red
            break;
    case 2: colorWipe(strip.Color(0, 64, 0), 50);  // Green
            break;
    case 3: colorWipe(strip.Color(0, 0, 64), 50);  // Blue
            break;
    case 4: theaterChase(strip.Color(32, 32, 32), 50); // White
            break;
    case 5: theaterChase(strip.Color(64,   0,   0), 50); // Red
            break;
    case 6: theaterChase(strip.Color(  0,   0, 64), 50); // Blue
            break;
    case 7: slowPulse(BLUE_PULSE, 0, 64, 50);
            break;
    case 8: slowPulse(RED_PULSE, 0, 64, 40);
            slowPulse(GREEN_PULSE, 0, 64, 40);
            slowPulse(BLUE_PULSE, 0, 64, 40);
            break;
    case 9: colorChase(strip.Color(127, 0, 127), 150);
            break;
    case 10: snakeChase(strip.Color(127, 0, 0), 100);
            break;
    //case 7: rainbow(20);
    //        break;
    //case 8: rainbowCycle(20);
    //        break;
    //case 9: theaterChaseRainbow(50);
    //        break;
  }
}



// a light that has a decreasing intensity tail runs through the strip
void snakeChase(uint32_t color, uint8_t wait) {
  uint32_t tail1, tail2, tail3;
  tail1 = strip.Color(red(color)>>1, green(color)>>1, blue(color)>>1);
  tail2 = strip.Color(red(tail1)>>1, green(tail1)>>1, blue(tail1)>>1);
  tail2 = strip.Color(red(tail2)>>1, green(tail2)>>1, blue(tail2)>>1);

  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    if (i>0) strip.setPixelColor(i-1, tail1);
    if (i>1) strip.setPixelColor(i-2, tail2);
    if (i>2) strip.setPixelColor(i-3, tail3);
    if (i>3) strip.setPixelColor(i-4, strip.Color(0,0,0));
    strip.show();
    delay(wait);
  }

  // set all the pixels to black
  strip.setPixelColor(strip.numPixels() - 1, strip.Color(0,0,0));
  strip.setPixelColor(strip.numPixels() - 2, strip.Color(0,0,0));
  strip.setPixelColor(strip.numPixels() - 3, strip.Color(0,0,0));
  strip.setPixelColor(strip.numPixels() - 4, strip.Color(0,0,0));
}

// color : 0 = r, 1 = g, 2 = b, 3 = w
void slowPulse(uint8_t color, uint8_t intensity_low, uint8_t intensity_high, uint8_t wait) {
  for(uint32_t i=intensity_low; i<=intensity_high; i++) {
    for(uint16_t j=0; j<strip.numPixels(); j++) {
      switch(color) {
        case RED_PULSE:
          strip.setPixelColor(j, strip.Color(i, 0, 0));
          break;
        case GREEN_PULSE:
          strip.setPixelColor(j, strip.Color(0, i, 0));
          break;
        case BLUE_PULSE:
          strip.setPixelColor(j, strip.Color(0, 0, i));
          break;
        default:
          strip.setPixelColor(j, strip.Color(i, i, i));
      }
      //strip.setPixelColor(j, i);
    }
    strip.show();
    delay(wait);
  }

  for(int32_t i=intensity_high; i>=intensity_low; i--) {
    for (uint16_t j=0; j<strip.numPixels(); j++) {
      switch(color) {
        case RED_PULSE:
          strip.setPixelColor(j, strip.Color(i, 0, 0));
          break;
        case GREEN_PULSE:
          strip.setPixelColor(j, strip.Color(0, i, 0));
          break;
        case BLUE_PULSE:
          strip.setPixelColor(j, strip.Color(0, 0, i));
          break;
        default:
          strip.setPixelColor(j, strip.Color(i, i, i));
      }
      //strip.setPixelColor(j, i);
    }
    strip.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// color runs along the led strip and back
void colorChase(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    if (i>0)
      strip.setPixelColor(i-1,0);
    strip.show();
    delay(wait);
  }

  for(int16_t i=strip.numPixels()-1; i>=0; i--) {
    strip.setPixelColor(i, c);
    if (i<strip.numPixels()-1)
      strip.setPixelColor(i+1, 0);
    strip.show();
    delay(wait);
  }

  strip.setPixelColor(0, 0);
  strip.show();
  delay(wait);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// 0 - 127
uint32_t WheelHalfIntensity(byte WheelPos) {
  WheelPos = 127 - WheelPos;
  if(WheelPos < 42) {
    return strip.Color(127 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 85) {
    WheelPos -= 42;
    return strip.Color(0, WheelPos * 3, 127 - WheelPos * 3);
  }
  WheelPos -= 85;
  return strip.Color(WheelPos * 3, 127 - WheelPos * 3, 0);
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
