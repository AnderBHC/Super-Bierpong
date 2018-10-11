
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
Adafruit_NeoPixel Strip = Adafruit_NeoPixel(2,40,NEO_RGB + NEO_KHZ800);
byte FeldA[11][5]={{36,37,39,38},{35,34,28,29},{33,32,30,31},{27,26,16,17},{25,24,18,19},{23,22,20,21},{15,14,0,1},{13,14,2,3},{11,10,4,5},{9,8,6,7}};
void setup(){
  Strip.begin();
  Strip.show();
}
void loop(){
	for (int i = 0; i<10; i++){
		for (int j = 0;j<4;j++){
			Strip.setPixelColor(FeldA[i][j],RainbowRot(i*77),RainbowGruen(i*77),RainbowBlau(i*77));
		}
		Strip.show();
		delay(1000);
		for (int k = 0;k<4;k++){
			Strip.setPixelColor(FeldA[i][k],0,0,0);
		}
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
		gruen = 512-c;
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