#include <Button.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define Pin 2

//Pinbelegung
const int PinButtonModus = 3;
const int PinButtonUmstellenA = 4;
const int PinButtonUmstellenB = 5;

//konstruktor für den LED streifen (Anzahl LEDs, Angeschlossener PIN, Modus)
Adafruit_NeoPixel strip = Adafruit_NeoPixel (20, PIN, NEO_RGB + NEO_KHZ800);

int Modus = 0; //0 Bierpong normal | 1 Bierpong Rainbow |  2 Bierpong Kings Cup | 3 Flipcup
int TeamA = 0;
int TeamB = 0;

int modusButton = 0;
Button ButtonModus(PinButtonModus);

int umstellenA = 0;
Button ButtonUmstellenA(PinUmstellenA);

int umstellenB = 0;
Button ButtonUmstellenB(PinUmstellenA);

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  modusButton = ButtonModus.update();
  umstellenA = ButtonUmstellenA.update();
  umstellenB = ButtonUmstellenB.update();

  switch (Modus){
    case(0){
      Bierpong();
      break
    }
    case(2){
      Kingscup();
      break
    }
    case(1){
      Rainbow();
      break
    }
    case(3){
      Flipcup();
      break
    }
    
}
  /*
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
