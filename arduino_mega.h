#pragma once
#include "LED.h"
#include <Adafruit_BMP085_U.h>
#include <Adafruit_BNO055.h>
#include <RTClib.h>
#include "sd_shield.h"
#include "OneWire.h"
#include <Adafruit_MotorShield.h>
#include "HIH6130.h"
//#include "Sparkfun_Humid.h"
#include "DallasTemperature.h"
#include <Adafruit_SI1145.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include "UV_Sensor.h"


class arduino_mega {
public:

	arduino_mega();
	DateTime getTime() const;
	Adafruit_MotorShield& motorshield() { return _motorShield; }
private:

	SD_Shield _logger;
	RTC_DS1307 _realTimeClock;
	LED _onboardLED;
	DallasTemperature _extTempSensor;
	Adafruit_BNO055 _bnoSensor;
	Adafruit_BMP085_Unified _bmpSensor;
	HIH6130 _humidSensor;
	Adafruit_MotorShield _motorShield;
	OneWire _OneWireBus;
	Adafruit_SI1145 _lightSensor;
	Adafruit_BicolorMatrix _ledMatrix;
	UV _UVSensor;
	

	
};
