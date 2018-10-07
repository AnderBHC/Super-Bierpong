#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define Pin 2

//konstruktor für den LED streifen (Anzahl LEDs, Angeschlossener PIN, Modus)
Adafruit_NeoPixel strip = Adafruit_NeoPixel (20, PIN, NEO_RGB + NEO_KHZ800);

int Modus = 0; //0 Bierpong normal | 1 Bierpong verschärft | 2 Flipcup
int TeamA = 0;
int TeamB = 0;

void setup() {
  strip.begin();
  strip.show();


}

void loop() {
  if (Modus == 0){
    if (TeamA == 0){
      for (int i = 0 ; i < 30 ; i++){
        strip.setPixelColor(i,0,255,0);
      }
  }
    if (TeamB == 0){
      for (int i = 30 ; i < 59 ; i++){
        strip.setPixelColor(i,0,255,0);
      }
    
  }
  if (Modus == 1){
    
  }
  if (Modus == 2){
    
  }
  // put your main code here, to run repeatedly:

}
