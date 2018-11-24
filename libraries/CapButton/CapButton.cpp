#include "Arduino.h"
#include "CapButton.h"
#include "CapacitiveSensor.h"

CapButton::CapButton(CapacitiveSensor& Sensor){
	_Sensor = &Sensor;
	lastDebounce = 0;
	oldstate = LOW;
	clickEnded = true;
	debouncetime = 50;
	treshhold = 1000;
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
		clickEnded = false;
		return 1; //click
	}

	//fallende flanke
	if (state == LOW && clickEnded == false && millis() - lastDebounce > debouncetime){
		clickEnded = true;
			return 0;
		}
	if (state!=oldstate){
		lastDebounce = millis();
		oldstate=state;
	}
	return 0; //keine eingabe
}
