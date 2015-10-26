#pragma once
#include "EventAction.h"
#include "Adafruit_BMP085_U.h"
#include <Adafruit_MotorShield.h>
#include "RTClib.h"
#include "EventData.h"
class arduino_mega;

CREATE_ACTION_1ARG(initMotorShield, const Adafruit_MotorShield& AFMS)
	bool isInit = false;
	Adafruit_MotorShield _afms;
END_CREATE


CREATE_ACTION_TWO_ARGS(doorman_altitude_check, Adafruit_BMP085_Unified bmp, arduino_mega* arduino)
	Adafruit_BMP085_Unified _bmp;
	arduino_mega* _arduino;
	Door_Data door1, door2;
END_CREATE

CREATE_ACTION(doorman_open)
	DateTime _doorOpenStart;
	DateTime _doorOpenFinish;
END_CREATE

CREATE_ACTION(turn_motor_on)
END_CREATE

CREATE_ACTION(doorman_close)
	DateTime _doorCloseStart;
	DateTime _doorCloseFinish;
END_CREATE

CREATE_ACTION_TWO_ARGS(turn_motor_off, Door_Data* doorInfo, const arduino_mega* arduino)
	Door_Data* door;
	const arduino_mega* _arduino;
END_CREATE