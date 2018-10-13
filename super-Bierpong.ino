#include <Button.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


//Pinbelegung
const int PinStreifen1 = 2;
const int PinStreifen2 = 3;
const int PinStreifen3 = 4;
const int PinStreifen4 = 5;
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


int Modus = 0; //0 Bierpong normal | 1 Bierpong Rainbow |  2 Bierpong Kings Cup | 3 Flipcup
int TeamA = 0; //0 alle | 1 Blume | 2 diamant | 3 aus
int TeamB = 0; //0 alle | 1 Blume | 2 diamant | 3 aus

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

//  modusButton = ButtonModus.update();
//  umstellenA = ButtonUmstellenA.update();
//  umstellenB = ButtonUmstellenB.update();

/* switch (Modus){
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
    
	} */
	Bierpong();
	Flipcup();
	StreifenFlipcup1.show();
	StreifenFlipcup2.show();
	StreifenBierpongA.show();
	StreifenBierpongB.show();
	
}

void Bierpong(){
	switch (TeamA){
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
					StreifenBierpongA.setPixelColor(FeldA[i][j], 127*Diamant[i], 127*Diamant[i], 0);
				}
			}
	
	}
	switch (TeamB){
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
					StreifenBierpongB.setPixelColor(FeldB[i][j], 127*Diamant[i], 127*Diamant[i], 0);
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
		long unsigned int offset = i*768/95*millis()/1000;
		StreifenFlipcup1.setPixelColor(i,RainbowRot(offset),RainbowGruen(offset),RainbowBlau(offset));
		StreifenFlipcup2.setPixelColor(94-i,RainbowRot(offset),RainbowGruen(offset),RainbowBlau(offset));
	}
}

byte RainbowRot(unsigned int offset){
  int c=offset%768;
  byte rot = 0;
  if (c<256){
    rot=255-c;
  }
  else if (c<512){
    rot = 0;
  }
  else{
    rot = c-512;
  }
  return {rot};
}
byte RainbowGruen(unsigned int offset){
  int c=offset%768;
  byte gruen = 0;
  if (c<256){
    gruen=c;
  }
  else if (c<512){
    gruen = 511-c;
  }
  else{
    gruen = 0;
  }
  return {gruen};
} 
byte RainbowBlau(unsigned int offset){
  int c=offset%768;
  byte blau = 0;
  if (c<256){
    blau = 0;
  }
  else if (c<512){
    blau =  c-256;
  }
  else{
    blau = 512-c;
  }
  return {blau};
}


