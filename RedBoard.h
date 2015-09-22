#pragma once
#include "LED.h"
#include <Adafruit_BNO055.h>
#include <RTClib.h>

class RedBoard {
public:

	RedBoard();
	void SensorSetup();
	void InitEvents();
private:

	LED _onboardLED;
	Adafruit_BNO055 _bnoSensor;
	RTC_DS1307 _realTimeClock;
};
