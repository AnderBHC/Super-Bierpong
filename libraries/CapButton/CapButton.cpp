#include "Arduino.h"
#include "CapButton.h"
#include "CapacitiveSensor.h"

CapButton::CapButton(CapacitiveSensor& Sensor){

	lastDebounce = 0;
	oldstate = LOW;
	clickStart = 0;
	clickEnded = true;
	longclicked = false;
	lastClick = 0;
	debouncetime = 50;
	_Sensor = &Sensor;
	treshhold = _Sensor -> capacitiveSensor(100)*1.1;
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
		//lastDebounce = millis();
		clickEnded = false;
		return 0; //keine eingabe
	}
	//Prüft, ob ein klicken + halten da ist.
	if (state == HIGH && clickEnded == false && millis() - clickStart > 2000 && longclicked == false){
		longclicked = true;
		return 2; //klicken + halten

	}
	//fallende flanke
	if (state == LOW && clickEnded == false && millis() - lastDebounce > debouncetime){
		clickEnded = true;
		//lastDebounce = millis();
		if (longclicked == true){
			longclicked = false;
			return 0;
			}
		if (clickStart - lastClick < 500){
			lastClick = millis();
			return 3; //doppel klick
		}
		else{
			lastClick = millis();
			return 1; // normaler klick
		}
	}

	if (state!=oldstate){
		lastDebounce = millis();
		oldstate=state;
	}
	return 0; //keine eingabe
}
