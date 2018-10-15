#include "Arduino.h"
#include "CapButton.h"
#include "CapacitiveSensor.h"

CapButton::CapButton(uint8_t pinRead, uint8_t pinSend){
	_pinRead = pinRead;
	_pinSend = pinSend;
	lastDebounce = 0;
	oldstate = LOW;
	clickStart = 0;
	clickEnded = true;
	longclicked = false;
	lastClick = 0;
	debouncetime = 100;
	CapacitiveSensor Sensor= CapacitiveSensor (_pinSend, _pinRead);
}

int CapButton::update(){
	int state = Sensor.capacitiveSensor(30);

	//steigende flanke
	if (state == HIGH && millis() - lastDebounce > debouncetime && clickEnded == true) {
		clickStart = millis();
		lastDebounce = millis();
		clickEnded = false;
		return 0;
	}
	//Prüft, ob ein klicken + halten da ist.
	if (state == HIGH && clickEnded == false && millis() - clickStart > 500 && longclicked == false){
		longclicked = true;
		return 2;

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
			return 3;
		}
		else{
			return 1;
		}
	}

	if (state!=oldstate){
		lastDebounce = millis();
		oldstate=state;
	}
	return 0;
}
