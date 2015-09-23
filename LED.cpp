#include "LED.h"
#include <Arduino.h>

LED::LED(uint8_t pin) : _ledPin(pin), _ledState(LOW) {

	pinMode(_ledPin, OUTPUT);
}


void LED::toggle() {
	if (_ledState == HIGH) _ledState = LOW;
	else _ledState = HIGH;
	digitalWrite(_ledPin, _ledState);
}
