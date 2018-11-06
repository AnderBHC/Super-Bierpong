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
	CapacitiveSensor Sensor= CapacitiveSensor (_pinSend, _pinRead);
	debouncetime = 50;
	
}

long  CapButton::rawSensor(){
	long total = _Sensor.capacitiveSensor(100);
	return total;
}
int CapButton::update(){
	long total=_Sensor.capacitiveSensor(100);
	
	int state = LOW;
	if (total>50){
		state=HIGH;
	}
/* 	Serial.print(total);
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
	if (state == HIGH && clickEnded == false && millis() - clickStart > 2000 && longclicked == false){
		longclicked = true;
		return 2; //klicken + halten

	}
	//fallende flanke
	if (state == LOW && clickEnded == false && millis() - lastDebounce > debouncetime){
		clickEnded = true;
		lastDebounce = millis();
		
		if (longclicked == true){
			longclicked = false;
			return 0;
			}
		if (clickStart - lastClick < 100){
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
