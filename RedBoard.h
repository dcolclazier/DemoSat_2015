#pragma once
#include "LED.h"
#include <Adafruit_BNO055.h>

class RedBoard {
public:

	RedBoard();

private:
	void SensorSetup();

	LED _onboardLED;
	Adafruit_BNO055 _bnoSensor;

};
