#include <DMXSerial.h>

void setup(){
  DMXSerial.init(DMXController);
  DMXSerial.maxChannel(66);
  for ( int i = 1; i <= 66; i++){
    DMXSerial.write(i,0);
  }
}

long last = 0;
int i = 1;
void loop(){
  
  DMXSerial.write(1,255);
/*
    DMXSerial.write(max(i-3, 0), 0);
    DMXSerial.write(max(i-2, 0), 0);
    DMXSerial.write(max(i-1, 0), 0);
    DMXSerial.write(i, 255);
    DMXSerial.write(i + 1, 255);
    DMXSerial.write(i + 2, 255);
    if (millis()-last > 500){
      i = i + 3;
      if (i > 66){
        i = 1;
      }
      last = millis();
    }
    */
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
