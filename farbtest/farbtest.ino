#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const int PinStrip = 2;
const int PixelStrip = 28;
Adafruit_NeoPixel Strip = Adafruit_NeoPixel (PixelStrip,PinStrip,NEO_GRB + NEO_KHZ800);

void setup(){
  Serial.begin(9600);
  Strip.begin();
  Strip.clear();
}

void loop(){
//  Serial.println(millis());
  if (Serial.available() > 0) {
    int color = Serial.parseInt();
    byte rot = RainbowRot(color);
    byte gruen = RainbowGruen(color);
    byte blau = RainbowBlau(color);
    for (int i = 0; i < 4; i++){
      Strip.setPixelColor(i, rot, gruen, blau);
    }
  Strip.show();
  Serial.print(color);
  Serial.print(": ");
  Serial.print(rot);
  Serial.print(", ");
  Serial.print(gruen);
  Serial.print(", ");
  Serial.print(blau);
  Serial.print("\n");
  }

}

byte RainbowRot(unsigned int offset){
  int c = offset%766;
  if (c >= 0 && c <= 255){
    return 255 - c;
  }
  if (c > 255 && c <= 510) {
    return 0;
  }
  if (c > 510){
    return c - 510;
  }
}
byte RainbowGruen(unsigned int offset){
  int c = offset%766;
  byte color;
  if (c >= 0 && c <= 255){
    return c;
  }
  if (c > 255 && c <= 510){
    return 510 - c;
  }
  if(c > 510){
    return 0;
  }
}
byte RainbowBlau(unsigned int offset){
  int c = offset%766;
  if(c >= 0 && c <= 255){
    return 0;
  }
  if (c>=256 && c<510){
    return c - 255;
  }
  if (c >= 510){
    return 765 - c;
  }
}
