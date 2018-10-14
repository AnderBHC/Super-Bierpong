/*
Libary for reading capacitive Buttons
*/
#ifndef CapButton_h
#define CapButton_h

#include "Arduino.h"
#include "CapacitiveSensor.h"

class Button
{
  public:
    Button(int pinread,pinsend);
	int update();
  private:
	CapacitiveSensor Sensor;
	int _treshhold;
    int _pinread;
	int _pinsend;
    int oldstate;
    long lastDebounce;
	long clickStart;
	boolean clickEnded;
	boolean longclicked;
	boolean state;
	long lastClick;
	int debouncetime;
};
#endif