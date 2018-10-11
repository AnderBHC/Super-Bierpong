#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

Adafruit_NeoPixel strip = Adafruit_NeoPixel (400, 2, NEO_RGB + NEO_KHZ800);

void setup() {
  strip.begin();
}

void loop(){
  for ( int i = 0; i < 95 ; i ++){
    strip.setPixelColor(i,255,0,0);
    strip.show();
    delay (250);
    strip.setPixelColor(i,0,0,0);
  }
    for ( int i = 0; i < 95 ; i ++){
    strip.setPixelColor(i,0,255,0);
    strip.show();
    delay (250);
    strip.setPixelColor(i,0,0,0);
  }
    for ( int i = 0; i < 95 ; i ++){
    strip.setPixelColor(i,0,0,255);
    strip.show();
    delay (250);
    strip.setPixelColor(i,0,0,0);
  }

}
