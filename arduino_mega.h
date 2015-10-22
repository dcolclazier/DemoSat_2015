#pragma once
#include "LED.h"
#include <Adafruit_BMP085_U.h>
#include <Adafruit_BNO055.h>
#include <RTClib.h>
#include "sd_shield.h"
#include "OneWire.h"
#include "HIH6130.h"
//#include "Sparkfun_Humid.h"
#include "DallasTemperature.h"

class arduino_mega {
public:

	arduino_mega();
	DateTime getTime() const;
private:

	SD_Shield _logger;
	RTC_DS1307 _realTimeClock;
	LED _onboardLED;
	DallasTemperature _extTempSensor;
	Adafruit_BNO055 _bnoSensor;
	Adafruit_BMP085_Unified _bmpSensor;
	HIH6130 _humidSensor;
	//Sparkfun_Humid _humidSensor;
	OneWire _OneWireBus;
};
