#include <CapButton.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


//Pinbelegung
const int PinStreifen1 = 2;
const int PinStreifen2 = 3;
const int PinStreifen3 = 4;
const int PinStreifen4 = 5;

const int PinCapacitiveSender = 9;
const int PinButtonModus = 6;
const int PinButtonUmstellenA = 7;
const int PinButtonUmstellenB = 8;

//konstruktor für den LED streifen (Anzahl LEDs, Angeschlossener PIN, Modus)
const int PixelStreifen1 = 95;
const int PixelStreifen2 = 95;
const int PixelStreifen3 = 40;
const int PixelStreifen4 = 40;
Adafruit_NeoPixel StreifenFlipcup1 = Adafruit_NeoPixel (95, PinStreifen1, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel StreifenFlipcup2 = Adafruit_NeoPixel (95, PinStreifen2, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel StreifenBierpongA = Adafruit_NeoPixel (40, PinStreifen3, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel StreifenBierpongB = Adafruit_NeoPixel (40, PinStreifen4, NEO_RGB + NEO_KHZ800);

//Konstruktor für die Taster (pinread, pinsend, tresshold)
CapButton ButtonModus = CapButton(PinButtonModus,PinCapacitiveSender,1000);
CapButton ButtonUmstellenA = CapButton(PinButtonUmstellenA,PinCapacitiveSender,1000);
CapButton ButtonUmstellenB = CapButton(PinButtonUmstellenB,PinCapacitiveSender,1000);

int Modus = 0; //0 Bierpong normal | 1 Bierpong Rainbow |  2 Bierpong Kings Cup | 3 Flipcup
int PunkteTeamA = 0; //0 alle | 1 Blume | 2 diamant | 3 aus
int PunkteTeamB = 0; //0 alle | 1 Blume | 2 diamant | 3 aus

byte FeldA[11][5]={{36,37,39,38},{35,34,28,29},{33,32,30,31},{27,26,16,17},{25,24,18,19},{23,22,20,21},{15,14,0,1},{13,14,2,3},{11,10,4,5},{9,8,6,7}};
byte FeldB[11][5]={{36,37,39,38},{35,34,28,29},{33,32,30,31},{27,26,16,17},{25,24,18,19},{23,22,20,21},{15,14,7,6},{13,12,5,4},{11,10,3,2},{9,8,1,0}};
byte Blume[11]={0,1,1,1,1,1,0,1,1,0};
byte Diamant[11]={1,1,1,0,1,0,0,0,0,0};

void setup() {
	StreifenFlipcup1.begin();
	StreifenFlipcup2.begin();
	StreifenBierpongA.begin();
	StreifenBierpongB.begin();

	StreifenFlipcup1.show();
	StreifenFlipcup2.show();
	StreifenBierpongA.show();
	StreifenBierpongB.show();
}

void loop() {

	int stateModusButton = ButtonModus.update();
	int stateUmstellenA = ButtonUmstellenA.update();
	int stateUmstellenB = ButtonUmstellenB.update();

	if (stateModusButton == 1){
		Modus ++;
	}
	if (Modus > 3){
		Modus = 0;
	}

	if (stateUmstellenA == 1){
		PunkteTeamB ++;
	}
	if (PunkteTeamB > 3){
		PunkteTeamB = 0;
	}
	if (stateUmstellenB == 1){
		PunkteTeamA ++;
	}
	if (PunkteTeamA > 3){
		PunkteTeamA = 0;
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

	StreifenFlipcup1.show();
	StreifenFlipcup2.show();
	StreifenBierpongA.show();
	StreifenBierpongB.show();

}

void Bierpong(){
	switch (PunkteTeamA){
		case(0):
			for (int i = 0; i<10; i++){
				for ( int j = 0; j < 4; j++){
					StreifenBierpongA.setPixelColor(FeldA[i][j], 0, 255, 0);
			}
		}
		case(1):
			for ( int i = 0; i < 10; i++ ){
				for ( int j = 0; j < 4; j++){
					StreifenBierpongA.setPixelColor(FeldA[i][j], 127*Blume[i], 127*Blume[i], 0);
				}
			}
		case(2):
			for ( int i = 0; i < 10; i++ ){
				for ( int j = 0; j < 4; j++){
					StreifenBierpongA.setPixelColor(FeldA[i][j], 255*Diamant[i], 0, 0);
				}
			}

	}
	switch (PunkteTeamB){
		case(0):
			for (int i = 0; i<10; i++){
				for ( int j = 0; j < 4; j++){
					StreifenBierpongB.setPixelColor(FeldB[i][j], 0, 255, 0);
			}
		}
		case(1):
			for ( int i = 0; i < 10; i++ ){
				for ( int j = 0; j < 4; j++){
					StreifenBierpongB.setPixelColor(FeldB[i][j], 127*Blume[i], 127*Blume[i], 0);
				}
			}
		case(2):
			for ( int i = 0; i < 10; i++ ){
				for ( int j = 0; j < 4; j++){
					StreifenBierpongB.setPixelColor(FeldB[i][j], 255*Diamant[i], 0*Diamant[i], 0);
				}
			}
	}
}
void Kingscup(){
  }
void Rainbow(){
  }
void Flipcup(){
	for (int i = 0; i < 95; i++){
		long unsigned int offset = i*768*millis()/(1000*95);
		StreifenFlipcup1.setPixelColor(i, RainbowRot(offset) ,RainbowGruen(offset), RainbowBlau(offset));
		StreifenFlipcup2.setPixelColor(94-i, RainbowRot(offset), RainbowGruen(offset), RainbowBlau(offset));
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
