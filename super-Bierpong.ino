#include <CapButton.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


//Pinbelegung
const int PinStripTriA = 2;
const int PinStripTriB = 5;
const int PinStripSideR = 3;
const int PinStripSideL = 4;

const int PinSend = 6;
const int PinButtonModus = 7;
const int PinButtonColor = 8;
const int PinButtonUmstellenA = 9;
const int PinButtonUmstellenB = 10;

//konstruktor für den LED streifen (Anzahl LEDs, Angeschlossener PIN, Modus)
const int PixelStripSideR = 95;
const int PixelStripSideL= 95;
const int PixelStripTriA= 40;
const int PixelStripTriB = 40;
Adafruit_NeoPixel StripSideL = Adafruit_NeoPixel (PixelStripSideL, PinStripSideL, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel StripSideR = Adafruit_NeoPixel (PixelStripSideR, PinStripSideR, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel StripTriA = Adafruit_NeoPixel (PixelStripTriA, PinStripTriA, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel StripTriB = Adafruit_NeoPixel (PixelStripTriB, PinStripTriB, NEO_RGB + NEO_KHZ800);

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
uint8_t PunkteTeamA = 0; //0 alle | 1 Blume | 2 diamant | 3 aus
uint8_t PunkteTeamB = 0; //0 alle | 1 Blume | 2 diamant | 3 aus

//addressern der Pixel in den einzelnen Bierpong Leuchtfeldern von oben nach unten von links nach rechts
byte FeldA[11][5]={{36,37,39,38},{35,34,28,29},{33,32,30,31},{27,26,16,17},{25,24,18,19},{23,22,20,21},{15,14,0,1},{13,14,2,3},{11,10,4,5},{9,8,6,7}};
byte FeldB[11][5]={{36,37,39,38},{35,34,28,29},{33,32,30,31},{27,26,16,17},{25,24,18,19},{23,22,20,21},{15,14,7,6},{13,12,5,4},{11,10,3,2},{9,8,1,0}};

//faktoren für einzelne Bierpong felder nach dem umstellen
byte Blume[11]={0,1,1,1,1,1,0,1,1,0};
byte Diamant[11]={1,1,1,0,1,0,0,0,0,0};
byte TrackerRandomFieldA[11]={0,0,0,0,0,0,0,0,0,0};
byte TrackerRandomFieldB[11]={0,0,0,0,0,0,0,0,0,0};
byte SetRandomFieldA[11]={0,0,0,0,0,0,0,0,0,0};
byte SetRandomFieldB[11]={0,0,0,0,0,0,0,0,0,0};

uint8_t stateModusButton;
uint8_t stateUmstellenButtonA;
uint8_t stateUmstellenButtonB;

int RandomFieldA = 0;
int RandomFieldB = 0;

void setup() {
  StripTriA.begin();
  StripTriB.begin();
  StripSideL.begin();
  StripSideR.begin();

  StripTriA.show();
  StripTriB.show();
  StripSideL.show();
  StripSideR.show();
}

void loop() {

//verarbeitung der eingabe der Kapizitativen Taster
//0 keine eingabe | 1 normaler klick | 2 klicken + halten | 3 doppel klick
  stateModusButton = ButtonModus.update();
  stateUmstellenButtonA = ButtonUmstellenA.update();
  stateUmstellenButtonB = ButtonUmstellenB.update();

  if (stateModusButton == 1){
    Modus ++;
    StripTriA.clear();
    StripTriB.clear();
    StripSideL.clear();
    StripSideR.clear();
    PunkteTeamA = 0;
    PunkteTeamB = 0;
    }

  if (Modus > 3){
    Modus = 0;
  }

  switch (Modus){
    case(0):
      Bierpong();
      break;

    case(1):
      Rainbow();
      break;

    case(2):
      Kingscup();
      break;
    case(3):
      Flipcup();
      break;
}

  StripTriA.show();
  StripTriB.show();
  StripSideL.show();
  StripSideR.show();

}

void Bierpong(){
  if (Modus != oldModus){
    oldModus = Modus;
    PunkteTeamA = 0;
    PunkteTeamB = 0;
  }
  if (stateUmstellenButtonA == 1){
    PunkteTeamB ++;
  }
  if (PunkteTeamB > 3){
    PunkteTeamB = 0;
  }
  if (stateUmstellenButtonB == 1){
    PunkteTeamA ++;
  }
  if (PunkteTeamA > 3){
    PunkteTeamA = 0;
  }
  switch (PunkteTeamA){
    case(0):
      for (int i = 0; i<10; i++){
        for ( int j = 0; j < 4; j++){
          StripTriA.setPixelColor(FeldA[i][j], 0, 255, 0);
      }
    }
    case(1):
      for ( int i = 0; i < 10; i++ ){
        for ( int j = 0; j < 4; j++){
          StripTriA.setPixelColor(FeldA[i][j], 127*Blume[i], 127*Blume[i], 0);
        }
      }
    case(2):
      for ( int i = 0; i < 10; i++ ){
        for ( int j = 0; j < 4; j++){
          StripTriA.setPixelColor(FeldA[i][j], 255*Diamant[i], 0, 0);
        }
      }

  }
  switch (PunkteTeamB){
    case(0):
      for (int i = 0; i<10; i++){
        for ( int j = 0; j < 4; j++){
          StripTriB.setPixelColor(FeldB[i][j], 0, 255, 0);
      }
    }
    case(1):
      for ( int i = 0; i < 10; i++ ){
        for ( int j = 0; j < 4; j++){
          StripTriB.setPixelColor(FeldB[i][j], 127*Blume[i], 127*Blume[i], 0);
        }
      }
    case(2):
      for ( int i = 0; i < 10; i++ ){
        for ( int j = 0; j < 4; j++){
          StripTriB.setPixelColor(FeldB[i][j], 255*Diamant[i], 0*Diamant[i], 0);
        }
      }
  }
}

void Kingscup(){
  int breakA;
  int breakB;

  if (oldModus !=Modus){ //neues Spiel beginnt
    oldModus = Modus;
    stateUmstellenButtonA = 1;
    stateUmstellenButtonB = 1;
    PunkteTeamA = 0;
    PunkteTeamB = 0;
    for (int i = 0; i < 10; i++){
      TrackerRandomFieldA[i] = 0;
      TrackerRandomFieldB[i] = 0;
    }
  }

  if (stateUmstellenButtonA == 1){
    RandomFieldA = rand() %(9-0)+0; //Generates number between 0 - 9
    breakA = 0;
    while (TrackerRandomFieldA[RandomFieldA] == 1 && breakA < 10){
      RandomFieldA++;
      breakA++;
      if (RandomFieldA >= 10){
        RandomFieldA = 0;
      }
    }
    TrackerRandomFieldA[RandomFieldA] = 1;
    for (int i = 0; i<10; i++) {
      SetRandomFieldA[i] = 0;
    }
    SetRandomFieldA[RandomFieldA] = 1;
  }
 if (PunkteTeamA > 0){
    PunkteTeamA = 0;
    for (int i = 0; i<10; i++) {
      TrackerRandomFieldA[i] = 0;
  }
}
  if (stateUmstellenButtonB == 1){
    RandomFieldB = rand() %(9-0)+0; //Generates number between 0 - 9
    breakB = 0;
    while (TrackerRandomFieldB[RandomFieldB] == 1 && breakB < 10){
      RandomFieldB++;
      breakB++;
      if (RandomFieldB >= 10){
        RandomFieldB = 0;
      }
    }
    TrackerRandomFieldB[RandomFieldB] = 1;
    for (int i = 0; i<10; i++) {
      SetRandomFieldB[i] = 0;
    }
    SetRandomFieldB[RandomFieldB] = 1;
  }
  if (PunkteTeamB > 0){
    PunkteTeamB = 0;
    for int i = 0; i < 10; i++){
      TrackerRandomFieldB[i] = 0;
    }
  }
  switch (breakA){
    case(10):
      PunkteTeamA = 1;
      for (int i = 0; i<10; i++){
        for ( int j = 0; j < 4; j++){
          StripTriA.setPixelColor(FeldA[i][j], 0, 255, 0);
      }
    }
    break;
    default:
      for ( int i = 0; i < 10; i++ ){
        for ( int j = 0; j < 4; j++){
          StripTriA.setPixelColor(FeldA[i][j], 255*SetRandomFieldA[i], 255*SetRandomFieldA[i], 255*SetRandomFieldA[i]);
        }
      }
      break;
  }
  switch (breakB){
    case(10):
    PunkteTeamB = 1;
      for (int i = 0; i<10; i++){
        for ( int j = 0; j < 4; j++){
          StripTriB.setPixelColor(FeldB[i][j], 0, 255, 0);
      }
    }
    break;
    default:
      for ( int i = 0; i < 10; i++ ){
        for ( int j = 0; j < 4; j++){
          StripTriB.setPixelColor(FeldB[i][j], 255*SetRandomFieldB[i], 255*SetRandomFieldB[i], 255*SetRandomFieldA[i]);
        }
      }
    break;
  }
}

void Rainbow(){
  if (Modus != oldModus){
    oldModus = Modus;
    PunkteTeamA = 0;
    PunkteTeamB = 0;
  }
  if (stateUmstellenButtonA == 1){
    PunkteTeamB ++;
  }
  if (PunkteTeamB > 3){
    PunkteTeamB = 0;
  }
  if (stateUmstellenButtonB == 1){
    PunkteTeamA ++;
  }
  if (PunkteTeamA > 3){
    PunkteTeamA = 0;
  }
  switch (PunkteTeamA){
    case(0):
      for (int i = 0; i<10; i++){
        int offset = i*766/10;
        for ( int j = 0; j < 4; j++){
          StripTriA.setPixelColor(FeldA[i][j], RainbowRot(offset), RainbowGruen(offset), RainbowBlau(offset));
      }
    }
    case(1):
      for ( int i = 0; i < 10; i++ ){
        int offset = i*766/10;
        for ( int j = 0; j < 4; j++){
          StripTriA.setPixelColor(FeldA[i][j], RainbowRot(offset)*Blume[i], RainbowGruen(offset)*Blume[i], RainbowBlau(offset)*Blume[i]);
        }
      }
    case(2):
      for ( int i = 0; i < 10; i++ ){
        int offset = i*766/10;
        for ( int j = 0; j < 4; j++){
          StripTriA.setPixelColor(FeldA[i][j], RainbowRot(offset)*Diamant[i], RainbowGruen(offset)*Diamant[i], RainbowBlau(offset)*Diamant[i]);
        }
      }

  }
  switch (PunkteTeamB){
    case(0):
      for (int i = 0; i<10; i++){
        int offset = i*766/10;
        for ( int j = 0; j < 4; j++){
          StripTriB.setPixelColor(FeldB[i][j],RainbowRot(offset) , RainbowGruen(offset), RainbowBlau(offset));
      }
    }
    case(1):
      for ( int i = 0; i < 10; i++ ){
        int offset = i*766/10;
        for ( int j = 0; j < 4; j++){
          StripTriB.setPixelColor(FeldB[i][j], RainbowRot(offset)*Blume[i], RainbowGruen(offset)*Blume[i], RainbowBlau(offset)*Blume[i]);
        }
      }
    case(2):
      for ( int i = 0; i < 10; i++ ){
        int offset = i*766/10;
        for ( int j = 0; j < 4; j++){
          StripTriB.setPixelColor(FeldB[i][j], RainbowRot(offset)*Diamant[i], RainbowGruen(offset)*Diamant[i], RainbowBlau(offset)*Diamant[i]);
        }
      }
  }
  Flipcup();
}

void Flipcup(){
  if (Modus != oldModus){
    oldModus = Modus;
  }
  for (int i = 0; i < PixelStripSideL; i++){
    long unsigned int offset = i*766/PixelStripSideL/2+millis()/1000;
    StripSideL.setPixelColor(i, RainbowRot(offset) ,RainbowGruen(offset), RainbowBlau(offset));
    StripSideR.setPixelColor(94-i, RainbowRot(offset), RainbowGruen(offset), RainbowBlau(offset));
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
  if (c > 510 and c <= 765){
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
  if (c >= 510 && c< 765){
    return 765 - c;
  }
}
