#include <CapButton.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <DMXSerial.h>

//Pinbelegung
#define PinStripTriA 5
#define PinStripTriB  2
#define PinStripSideR  3
#define PinStripSideL  4

#define PinSend  12
#define PinButtonModus 6
#define PinButtonUmstellenA  7
#define PinButtonUmstellenB  8

#define DMXStart 1 //Start Adresse für die verwendung im DMX betrieb
#define PinDMXControl 14 //umschalt am Transreciver
#define PinDMXMode 19 //Schalter zum einschalten des DMX

//konstruktor für den LED streifen (Anzahl LEDs, Angeschlossener PIN, Modus)
#define PixelStripSide 94
#define PixelStripTri 40
Adafruit_NeoPixel StripSideL = Adafruit_NeoPixel (PixelStripSide, PinStripSideL, NEO_GRB + NEO_KHZ800);
/*
Adafruit_NeoPixel StripSideL = Adafruit_NeoPixel (PixelStripSide, PinStripSideL, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel StripSideR = Adafruit_NeoPixel (PixelStripSide, PinStripSideR, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel StripTriA = Adafruit_NeoPixel (PixelStripTri, PinStripTriA, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel StripTriB = Adafruit_NeoPixel (PixelStripTri, PinStripTriB, NEO_GRB + NEO_KHZ800);

//Konstruktor für die Sensoren CapacitiveSensor(send,read)
CapacitiveSensor SensorModus = CapacitiveSensor(PinSend, PinButtonModus);
CapacitiveSensor SensorUmstellenA = CapacitiveSensor(PinSend, PinButtonUmstellenA);
CapacitiveSensor SensorUmstellenB = CapacitiveSensor(PinSend, PinButtonUmstellenB);
//Konstruktor für die Taster (Sensor)
CapButton ButtonModus = CapButton(SensorModus);
CapButton ButtonUmstellenA = CapButton(SensorUmstellenA);
CapButton ButtonUmstellenB = CapButton(SensorUmstellenB);

uint8_t Modus = 0; //0 Bierpong normal | 1 Bierpong Rainbow |  2 Bierpong Kings Cup | 3 Flipcup
uint8_t oldModus = 0;
uint8_t PunkteTeamA = 0; //0 alle | 1 Blume | 2 diamant
uint8_t PunkteTeamB = 0; //0 alle | 1 Blume | 2 diamant

//addressern der Pixel in den einzelnen Bierpong Leuchtfeldern von oben nach unten von links nach rechts
const byte FeldA[11][5]={{36,37,39,38},{35,34,28,29},{33,32,30,31},{27,26,16,17},{25,24,18,19},{23,22,20,21},{6,7,14,15},{4,5,12,13},{2,3,10,11},{0,1,8,9}};
const byte FeldB[11][5]={{36,37,39,38},{35,34,28,29},{33,32,30,31},{27,26,16,17},{25,24,18,19},{23,22,20,21},{0,1,14,15},{2,3,12,13},{4,5,10,11},{6,7,8,9}};

//faktoren für einzelne Bierpong felder nach dem umstellen
const byte Blume[11]={0,1,1,1,1,1,0,1,1,0};
const byte Diamant[11]={1,1,1,0,1,0,0,0,0,0};
byte TrackerRandomFieldA[11]={0,0,0,0,0,0,0,0,0,0};
byte TrackerRandomFieldB[11]={0,0,0,0,0,0,0,0,0,0};
byte SetRandomFieldA[11]={0,0,0,0,0,0,0,0,0,0};
byte SetRandomFieldB[11]={0,0,0,0,0,0,0,0,0,0};

uint8_t stateModusButton;
uint8_t stateUmstellenButtonA;
uint8_t stateUmstellenButtonB;

int RandomFieldA = 0;
int RandomFieldB = 0;
*/
uint8_t *RXBuffer;
uint8_t oldRXBuffer[67];

void setup() {
  /*
  StripTriA.begin();
  StripTriB.begin();
  StripSideL.begin();
  StripSideR.begin();

  StripTriA.show();
  StripTriB.show();
  StripSideL.show();
  StripSideR.show();

  pinMode(PinDMXMode,INPUT);
*/
  StripSideL.begin();
  DMXSerial.init(DMXReceiver, PinDMXControl);
  RXBuffer = DMXSerial.getBuffer();
  pinMode(10,OUTPUT);
  analogWrite(10,255);
}

void loop() {
  DMX();


  //StripTriA.show();
  //StripTriB.show();
  StripSideL.show();
  //StripSideR.show();
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

void DMX(){
  if (DMXSerial.dataUpdated()){
    DMXSerial.resetUpdated();
/*    for ( int i = 0; i < 3; i = i+3){
    if (oldRXBuffer[i] == RXBuffer[i + DMXStart]
      && oldRXBuffer[i + 1] == RXBuffer[i + 1 + DMXStart]
      && oldRXBuffer[i + 2] == RXBuffer[i + 2 + DMXStart]){
      setFielColor(i/3,oldRXBuffer[i], oldRXBuffer[i+1], oldRXBuffer[i+2]);
    }
    oldRXBuffer[i]=RXBuffer[i + DMXStart];
    oldRXBuffer[i+1] = RXBuffer[i + DMXStart + 1];
    oldRXBuffer[i+2] = RXBuffer[i + DMXStart + 2];
  }*/
  //setFieldColor (0,RXBuffer[1],RXBuffer[2],RXBuffer[3]);
  analogWrite(10,DMXSerial.read(1));
//  for (int i = 0; i < 1; i++){
//    StripSideL.setPixelColor(i*3,RXBuffer[i*3+DMXStart], RXBuffer[i*3+DMXStart+1], RXBuffer[i*3+DMXStart+2]);
  }
  }
}
