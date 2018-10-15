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

const int PinButtonSend = 6;
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

//Konstruktor für die Taster (pinread, pinsend, tresshold)
CapButton ButtonModus = CapButton(PinButtonModus, PinButtonSend);
CapButton ButtonUmstellenA = CapButton(PinButtonUmstellenA, PinButtonSend);
CapButton ButtonUmstellenB = CapButton(PinButtonUmstellenB, PinButtonSend);
CapButton ButtonColor = CapButton(PinButtonColor, PinButtonSend);

int Modus = 0; //0 Bierpong normal | 1 Bierpong Rainbow |  2 Bierpong Kings Cup | 3 Flipcup
int PunkteTeamA = 0; //0 alle | 1 Blume | 2 diamant | 3 aus
int PunkteTeamB = 0; //0 alle | 1 Blume | 2 diamant | 3 aus

//addressern der Pixel in den einzelnen Bierpong Leuchtfeldern von oben nach unten von links nach rechts
byte FeldA[11][5]={{36,37,39,38},{35,34,28,29},{33,32,30,31},{27,26,16,17},{25,24,18,19},{23,22,20,21},{15,14,0,1},{13,14,2,3},{11,10,4,5},{9,8,6,7}};
byte FeldB[11][5]={{36,37,39,38},{35,34,28,29},{33,32,30,31},{27,26,16,17},{25,24,18,19},{23,22,20,21},{15,14,7,6},{13,12,5,4},{11,10,3,2},{9,8,1,0}};

//faktoren für einzelne Bierpong felder nach dem umstellen
byte Blume[11]={0,1,1,1,1,1,0,1,1,0};
byte Diamant[11]={1,1,1,0,1,0,0,0,0,0};

uint8_t stateModusButton = ButtonModus.update();
uint8_t stateUmstellenButtonA = ButtonUmstellenA.update();
uint8_t stateUmstellenButtonB = ButtonUmstellenB.update();
uint8_t stateColorButton = ButtonColor.update();

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
  stateColorButton = ButtonColor.update();

	if (stateModusButton == 1){
		Modus ++;
	}
	if (Modus > 3){
		Modus = 0;
	}

	switch (Modus){
		case(0):
			Bierpong();
			break;

		case(2):
			Kingscup();
			break;

		case(1):
			Rainbow();
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
  }
void Rainbow(){
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 4; j++){
      int offset = i*766/10;
      StripTriA.setPixelColor(FeldA[i][j], RainbowRot(offset), RainbowGruen(offset), RainbowBlau(offset));
      StripTriB.setPixelColor(FeldB[i][j], RainbowRot(offset), RainbowGruen(offset), RainbowBlau(offset));
      Flipcup();
    }
  }
  }
void Flipcup(){
	for (int i = 0; i < 95; i++){
		long unsigned int offset = i*766*millis()/(1000*95);
		StripSideL.setPixelColor(i, RainbowRot(offset) ,RainbowGruen(offset), RainbowBlau(offset));
		StripSideR.setPixelColor(94-i, RainbowRot(offset), RainbowGruen(offset), RainbowBlau(offset));
	}
}

byte RainbowRot(unsigned int offset){
  int c = offset%766;
  byte rot = 0;
  if (c >= 0 && c <= 255){
    rot = 255-c;
  }
  if (c > 510 and c <= 765){
    rot = c-510;
  }
  return rot;
}
byte RainbowGruen(unsigned int offset){
  int c = offset%766;
  byte gruen = 0;
  if (c >= 0 && c <= 255){
    gruen=c;
  }
  if (c > 255 && c < 510){
    gruen = 510 - c;
  }
  return gruen;
}
byte RainbowBlau(unsigned int offset){
  int c = offset%766;
  byte blau = 0;
  if (c>=256 && c<510){
    blau = c-255;
  }
	if (c >= 510 && c< 765){
    blau = 765-c;
  }
  return blau;
}
