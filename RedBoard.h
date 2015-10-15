#pragma once
#include "LED.h"
#include <Adafruit_BMP085_U.h>
#include <Adafruit_BNO055.h>
#include <RTClib.h>
#include "Logger.h"

class Mega2560 {
public:

	Mega2560();
	DateTime getTime();
private:

	Logger _logger;
	RTC_DS1307 _realTimeClock;
	LED _onboardLED;
	Adafruit_BNO055 _bnoSensor;
	Adafruit_BMP085_Unified _bmpSensor;
};
