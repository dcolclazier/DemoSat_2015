#include "LED.h"
#include <Arduino.h>

LED::LED(int pin) {
	_ledPin = pin;
	pinMode(_ledPin, OUTPUT);
	_ledState = LOW;
	_prevMillis = 0;
}

void LED::Flash(int onTime, int offTime) {

	// check to see if it's time to change the state of the LED
	unsigned long currentMillis = millis();

	if (_ledState == HIGH && currentMillis - _prevMillis >= onTime) {
		_prevMillis = currentMillis;  // Remember the time
		toggle(LOW);
	}
	else if (_ledState == LOW && currentMillis - _prevMillis >= offTime) {
		_prevMillis = currentMillis;   // Remember the time
		toggle(HIGH);
	}

}
void LED::toggle() {
	if (_ledState == HIGH) toggle(LOW);
	else toggle(HIGH);
}

void LED::toggle(int pinState) {
	_ledState = pinState;
	digitalWrite(_ledPin, _ledState);
}