/*
Bibliothek fürs auslesen der Taster.
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
  private:
	CapacitiveSensor *_Sensor;
	long treshhold;
  boolean oldstate;
  long lastDebounce;
	boolean clickEnded;
	int debouncetime;
};
#endif
