#pragma once
#include "EventAction.h"
#include "EventArgs.h"
#include "Adafruit_BNO055.h"

ACTION(bno_gyro_update) {
	UNARYACTIONINIT(bno_gyro_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	//GyroData _gyro;
};
