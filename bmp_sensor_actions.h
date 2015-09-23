#pragma once
#include "EventHandler.h"
#include <Adafruit_BMP085_U.h>

ACTION(bmp_full_update) {
	UNARYACTIONINIT(bmp_full_update, Adafruit_BMP085_Unified bmp);
private:
	Adafruit_BMP085_Unified _bmp;
	bmp_full_args _args;
	const float _seaLevelPressure = 1012.8f;
};