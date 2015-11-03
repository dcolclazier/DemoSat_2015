#pragma once
#include "EventAction.h"
#include "Adafruit_BMP085_U.h"
#include <Adafruit_MotorShield.h>
#include "RTClib.h"
#include "EventData.h"
class arduino_mega;

CREATE_ACTION_1ARG(initMotorShield, const Adafruit_MotorShield& motorShield)
	bool isInit = false;
	Adafruit_MotorShield _motorShield;
	arduino_mega* _arduino;
END_CREATE


CREATE_ACTION_TWO_ARGS(doorman_altitude_check, Adafruit_BMP085_Unified bmp, arduino_mega* arduino)
	Adafruit_BMP085_Unified _bmp;
	arduino_mega* _arduino;
	Door_Data door1, door2;
END_CREATE

CREATE_ACTION_1ARG(doorman_open, arduino_mega* arduino)
	DateTime _doorOpenStart;
	DateTime _doorOpenFinish;
	arduino_mega* _arduino;
	END_CREATE

CREATE_ACTION_1ARG(turn_motor_on, arduino_mega* arduino)
	arduino_mega* _arduino;
	END_CREATE

CREATE_ACTION_1ARG(doorman_close, arduino_mega* arduino)
	DateTime _doorCloseStart;
	DateTime _doorCloseFinish;
	arduino_mega* _arduino;
END_CREATE

CREATE_ACTION_TWO_ARGS(turn_motor_off, Door_Data* doorInfo, arduino_mega* arduino)
	Door_Data* door;
	arduino_mega* _arduino;
END_CREATE