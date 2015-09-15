#pragma once
#include "EventAction.h"
#include "EventArgs.h"
#include "Adafruit_BNO055.h"

ACTION(bno_orientation_update) {
	UNARYACTIONINIT(bno_orientation_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
};