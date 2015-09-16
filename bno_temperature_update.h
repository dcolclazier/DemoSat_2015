#pragma once
#include "EventAction.h"
#include "EventArgs.h"
#include "Adafruit_BNO055.h"

ACTION(bno_temperature_update) {
	UNARYACTIONINIT(bno_temperature_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	//Temperature _temp;
};
