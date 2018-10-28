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
	debouncetime = 100;
	_Sensor = &Sensor;
	_treshhold = 150;
}

long CapButton::readRaw(){

	long total = _Sensor->capacitiveSensor(100);
	return total;
}
int CapButton::update(){
	long total = _Sensor->capacitiveSensor(100);
	state = LOW;
	if (total > _treshhold){
		state = HIGH;
	}
	/*
	Serial.print(total);
	Serial.print("\t");
	Serial.print(state);
	Serial.print("\n");
	*/

	//steigende flanke
	if (state == HIGH && millis() - lastDebounce > debouncetime && clickEnded == true) {
		clickStart = millis();
		lastDebounce = millis();
		clickEnded = false;
		return 0; //keine eingabe
	}
	//Prüft, ob ein klicken + halten da ist.
	if (state == HIGH && clickEnded == false && millis() - clickStart > 500 && longclicked == false){
		longclicked = true;
		return 2; //klicken + halten

	}
	//fallende flanke
	if (state == LOW && clickEnded == false && millis() - lastDebounce > debouncetime){
		clickEnded = true;
		lastDebounce = millis();
		lastClick = millis();
		if (longclicked == true){
			longclicked = false;
			return 0;
			}
		if (clickStart - lastClick < 500){
			return 3; //doppel klick
		}
		else{
			return 1; // normaler klick
		}
	}

	if (state!=oldstate){
		lastDebounce = millis();
		oldstate=state;
	}
	return 0; //keine eingabe
}
