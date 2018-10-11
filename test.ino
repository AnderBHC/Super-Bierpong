
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
			Strip.setPixelColor(FeldA[i][j],255,255,255);
		}
		Strip.show();
		delay(1000);
		for (int k = 0;k<4;k++){
			Strip.setPixelColor(FeldA[i][k],0,0,0);
		}
	}
}
