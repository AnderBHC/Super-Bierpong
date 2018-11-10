#include "Arduino.h"
#include "CapButton.h"
#include "CapacitiveSensor.h"

CapButton::CapButton(CapacitiveSensor& Sensor){
	_Sensor = &Sensor;
	lastDebounce = 0;
	oldstate = LOW;
	clickStart = 0;
	clickEnded = true;
	longclicked = false;
	lastClick = 0;
	debouncetime = 50;
	treshhold = 1000;
	clickTime = 500;

}

long CapButton::readRaw(){

	long total = _Sensor->capacitiveSensor(100);
	return total;
}
int CapButton::update(){
	long total = _Sensor->capacitiveSensor(100);
	boolean state = LOW;
	if (total > treshhold){
		state = HIGH;
	}


	//steigende flanke
	if (state == HIGH && millis() - lastDebounce > debouncetime && clickEnded == true) {
		clickStart = millis();
		clickEnded = false;
		return 0; //keine eingabe
	}
	//Prüft, ob ein klicken + halten da ist.
	if (state == HIGH && clickEnded == false && millis() - clickStart > 500 && longclicked == false){
		longclicked = true;
		return 1; //klicken + halten

	}
	//fallende flanke
	if (state == LOW && clickEnded == false && millis() - lastDebounce > debouncetime){
		clickEnded = true;
		if (longclicked == true){
			longclicked = false;
			return 0;
			}
		else{
			lastClick = millis();
			return 0;
		}
	}

	if (state!=oldstate){
		lastDebounce = millis();
		oldstate=state;
	}
	return 0; //keine eingabe
}
