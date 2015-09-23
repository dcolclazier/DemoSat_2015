#pragma once
#include <Arduino.h>

class LED {

public:
	void toggle();
	LED(uint8_t pin);
protected:
	uint8_t _ledPin;
	uint8_t _ledState;
};
