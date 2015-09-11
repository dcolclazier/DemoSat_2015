#pragma once
#include "EventHandler.h"
#include "EventAction.h"
#include "LED.h"
#include "LEDFlash.h"
#include "BNOTest.h"

class RedBoard {
public:
	RedBoard();

private:
	LED _onboardLED;
	Adafruit_BNO055 _bnoSensor;

};
