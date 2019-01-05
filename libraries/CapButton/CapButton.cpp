#include "Arduino.h"
#include "CapButton.h"
#include "CapacitiveSensor.h"

CapButton::CapButton(CapacitiveSensor& Sensor){
	_Sensor = &Sensor;
	lastDebounce = 0;
	oldstate = LOW;
	clickEnded = true;
	debouncetime = 100;
	treshholdHigh = 1000;
	treshholdLow = 500;
}

int CapButton::update(){
	long total = _Sensor->capacitiveSensor(100);
	boolean state = oldstate;
	if (state == LOW && total > treshholdHigh){
		state = HIGH;
	}
	else if(state == HIGH && total < treshholdLow){
		state = LOW;
	}
	//steigende flanke
	if (state == HIGH && millis() - lastDebounce > debouncetime && clickEnded == true) {
		clickEnded = false;
		return 1; //click
	}

	//fallende flanke
	if (state == LOW && clickEnded == false && millis() - lastDebounce > debouncetime){
		clickEnded = true;
			return 0; //keine eingabe
		}
	if (state!=oldstate){
		lastDebounce = millis();
		oldstate=state;
	}
	return 0; //keine eingabe
}
