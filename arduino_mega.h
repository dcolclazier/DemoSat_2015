#pragma once
#include "LED.h"
#include <Adafruit_BMP085_U.h>
#include <Adafruit_BNO055.h>
#include <RTClib.h>
#include "sd_shield.h"

class arduino_mega {
public:

	arduino_mega();
	DateTime getTime();
private:

	SD_Shield _logger;
	RTC_DS1307 _realTimeClock;
	LED _onboardLED;
	Adafruit_BNO055 _bnoSensor;
	Adafruit_BMP085_Unified _bmpSensor;
};
