/*
Libary for reading capacitive Buttons
*/
#ifndef CapButton_h
#define CapButton_h

#include "Arduino.h"
#include "CapacitiveSensor.h"

class CapButton
{
  public:
    CapButton(CapacitiveSensor& Sensor);
	   int update();
     long readRaw ();
  private:
	CapacitiveSensor *_Sensor;
	long _treshhold;
  boolean oldstate;
  long lastDebounce;
	long clickStart;
	boolean clickEnded;
	boolean longclicked;
	boolean state;
	long lastClick;
	int debouncetime;
};
#endif
