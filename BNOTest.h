#pragma once
#include "EventAction.h"
#include "EventArgs.h"
#include "Adafruit_BNO055.h"

ACTION(BNOTest) {
	UNARYACTIONINIT(BNOTest, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
};