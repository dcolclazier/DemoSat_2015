﻿#pragma once

class LED {

public:

	void Flash(int onTime, int offTime);
	void toggle();
	void toggle(int);
	explicit LED(int pin);

protected:
	LED() : _ledPin(0), _ledState(0), _prevMillis(0) {}
	int _ledPin;
	int _ledState;
	unsigned long _prevMillis;

};