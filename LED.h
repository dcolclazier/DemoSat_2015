#pragma once

class LED {

public:

	void Flash(int onTime, int offTime);
	void toggle();
	void toggle(int);
	LED(int pin);

	LED() : _ledPin(0), _ledState(0), _prevMillis(0) {}
protected:
	int _ledPin;
	int _ledState;
	unsigned long _prevMillis;

};
