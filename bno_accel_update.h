#pragma once
#include "EventAction.h"
#include "EventArgs.h"
#include "Adafruit_BNO055.h"

ACTION(bno_accel_update) {
	UNARYACTIONINIT(bno_accel_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	//AccelVector _acceleration;
};
