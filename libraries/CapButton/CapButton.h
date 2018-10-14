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
    CapButton(uint8_t pinread, uint8_t pinsend, unsigned int tresshold);
	int update();
  private:
	CapacitiveSensor& Sensor;
	unsigned int _treshhold;
  uint8_t _pinRead;
	uint8_t _pinSend;
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
