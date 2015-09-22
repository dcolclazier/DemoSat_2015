#include "LED.h"
#include <Arduino.h>

LED::LED(byte pin) : _ledPin(pin), _ledState(LOW) {

	pinMode(_ledPin, OUTPUT);
}


void LED::toggle() {
	if (_ledState == HIGH) {
		digitalWrite(_ledPin, LOW);
		_ledState = LOW;
	}
	else {
		digitalWrite(_ledPin, HIGH);
		_ledState = HIGH;
	}
}
