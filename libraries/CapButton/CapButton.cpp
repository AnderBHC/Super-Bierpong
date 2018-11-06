#include "Arduino.h"
#include "CapButton.h"
#include "CapacitiveSensor.h"

CapButton::CapButton(uint8_t pinRead, uint8_t pinSend){
	_pinRead = pinRead;
	_pinSend = pinSend;
CapButton::CapButton(CapacitiveSensor& Sensor){

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
=======
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

>>>>>>> c4275df3c6038977776678ea4fd15f65719ed85b
	//steigende flanke
	if (state == HIGH && millis() - lastDebounce > debouncetime && clickEnded == true) {
		clickStart = millis();
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
		
=======
		//lastDebounce = millis();
>>>>>>> c4275df3c6038977776678ea4fd15f65719ed85b
		if (longclicked == true){
			longclicked = false;
			return 0;
			}
<<<<<<< HEAD
		if (clickStart - lastClick < 100){
=======
		if (clickStart - lastClick < 500){
>>>>>>> c4275df3c6038977776678ea4fd15f65719ed85b
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
