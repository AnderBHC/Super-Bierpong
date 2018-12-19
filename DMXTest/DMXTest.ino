#include <DMXSerial.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PinStripTriA 5
#define PinStripTriB  2
#define PinStripSideR  3
#define PinStripSideL  4

#define PixelStripSide 94
#define PixelStripTri 40

uint8_t *RXBuffer;

Adafruit_NeoPixel StripSideL = Adafruit_NeoPixel (PixelStripSide, PinStripSideL, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel StripSideR = Adafruit_NeoPixel (PixelStripSide, PinStripSideR, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel StripTriA = Adafruit_NeoPixel (PixelStripTri, PinStripTriA, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel StripTriB = Adafruit_NeoPixel (PixelStripTri, PinStripTriB, NEO_GRB + NEO_KHZ800);


const byte FeldB[11][5]={{36,37,39,38},{35,34,28,29},{33,32,30,31},{27,26,16,17},{25,24,18,19},{23,22,20,21},{0,1,14,15},{2,3,12,13},{4,5,10,11},{6,7,8,9}};
const byte FeldA[11][5]={{36,37,39,38},{35,34,28,29},{33,32,30,31},{27,26,16,17},{25,24,18,19},{23,22,20,21},{6,7,14,15},{4,5,12,13},{2,3,10,11},{0,1,8,9}};

void setup(){
  StripTriA.begin();
  StripTriB.begin();
  StripSideL.begin();
  StripSideR.begin();

  StripTriA.clear();
  StripTriB.clear();
  StripSideL.clear();
  StripSideR.clear();

  StripSideL.setBrightnes(80);
  StripSideR.setBrightnes(80);

  StripTriA.show();
  StripTriB.show();
  StripSideL.show();
  StripSideR.show();

  DMXSerial.init(DMXProbe,13);
  RXBuffer = DMXSerial.getBuffer();

}


void loop(){

  if (DMXSerial.receive()){
    for (int i = 0; i < 22; i++)
    setFieldColor(i,RXBuffer[i*3+1],RXBuffer[i*3+2],RXBuffer[i*3+3]);

  }
    StripTriA.show();
    StripTriB.show();
    StripSideL.show();
    StripSideR.show();

}

void setFieldColor(uint8_t field, uint8_t red, uint8_t green, uint8_t blue){
  if (field < 10){
    for (int i = 0; i < 4; i++){
      StripTriA.setPixelColor(FeldA[field][i], red, green, blue);
    }
  }
    else if (field < 20){
      for(int i = 0; i < 4; i++){
        StripTriB.setPixelColor(FeldB[field-10][i], red, green, blue);
      }
    }
    else if (field == 20){
      for (int i = 0; i < PixelStripSide; i++){
        StripSideL.setPixelColor(i, red, green, blue);
      }
    }
    else if (field == 21){
      for(int i = 0; i < PixelStripSide; i++){
        StripSideR.setPixelColor(i, red, green, blue);
      }
    }
}
