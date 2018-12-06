#include <DMXSerial.h>

void setup(){
  DMXSerial.init(DMXController);
  DMXSerial.maxChannel(66);
}

long last = 0;
unsigned int c = 0;
void loop(){
  if (millis()-last > 10){
    for(int i = 0; i <= 66, i = i + 3){
      int offset = i*766/10+(millis()/4);
      DMXSerial.write(i, RainbowRot(offset));
      DMXSerial.write(i+1,RainbowGruen(offset));
      DMXSerial.write(i+2,RainbowBlau(offset));
    }
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
