#pragma once
#include "LED.h"
#include <Adafruit_BNO055.h>

class RedBoard {
public:
	void SensorSetup();

	RedBoard();

private:
	LED _onboardLED;
	Adafruit_BNO055 _bnoSensor;

};
