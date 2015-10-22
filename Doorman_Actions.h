#pragma once
#include "EventAction.h"
#include "Adafruit_BMP085_U.h"
#include "RTClib.h"
#include "EventData.h"
class arduino_mega;

CREATE_ACTION_TWO_ARGS(doorman_altitude_check, Adafruit_BMP085_Unified bmp, arduino_mega* arduino)
	Adafruit_BMP085_Unified _bmp;
	arduino_mega* _arduino;
	Door_Data door1, door2, door3, door4;
END_CREATE

CREATE_EVENT_TRIGGERING_ACTION(doorman_open, DoorOpen_Data)

DateTime _doorOpenStart;
DateTime _doorOpenFinish;

END_CREATE

CREATE_EVENT_TRIGGERING_ACTION(move_door, Door_Data)

END_CREATE

CREATE_EVENT_TRIGGERING_ACTION(doorman_close, DoorClose_Data)

DateTime _doorCloseStart;
DateTime _doorCloseFinish;

END_CREATE

CREATE_EVENT_TRIGGERING_ACTION_2ARGS(motor_on, Door_Data , Door_Data* doorInfo, const arduino_mega* arduino)
	Door_Data* _data;
	const arduino_mega* _arduino;
	bool off = false;
	unsigned long motor_run_time = 2750; // in milliseconds
END_CREATE