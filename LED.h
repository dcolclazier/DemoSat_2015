#pragma once
#include <Arduino.h>

class LED {

public:
	void toggle();
	LED(byte pin);
protected:
	byte _ledPin;
	byte _ledState;
};
