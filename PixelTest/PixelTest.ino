#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const byte StripLength = 93;
const byte Pin = 2;
Adafruit_NeoPixel strip = Adafruit_NeoPixel (StripLength, Pin, NEO_RGB + NEO_KHZ800);

void setup() {
  strip.begin();
}

void loop(){
  for ( int i = 0; i < StripLength ; i ++){
    strip.setPixelColor(i,255,0,0);
    strip.show();
    delay (250);
    strip.setPixelColor(i,0,0,0);
  }
    for ( int i = 0; i < StripLength ; i ++){
    strip.setPixelColor(i,0,255,0);
    strip.show();
    delay (250);
    strip.setPixelColor(i,0,0,0);
  }
    for ( int i = 0; i < StripLength ; i ++){
    strip.setPixelColor(i,0,0,255);
    strip.show();
    delay (250);
    strip.setPixelColor(i,0,0,0);
  }

}
