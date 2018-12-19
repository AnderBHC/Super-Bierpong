#include <DMXSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

uint8_t *RXBuffer;
Adafruit_NeoPixel Strip=Adafruit_NeoPixel(40, 2, NEO_GRB + NEO_KHZ800);

void setup(){
  Strip.begin();
  Strip.clear();
  DMXSerial.init(DMXProbe,13);
  RXBuffer = DMXSerial.getBuffer();

}


void loop(){

  if (DMXSerial.receive()){
    for(int i = 0; i < 22; i++)
    Strip.setPixelColor(i,RXBuffer[i*3+1],RXBuffer[i*3+2],RXBuffer[i*3+3]);
  }

    Strip.show();
}
