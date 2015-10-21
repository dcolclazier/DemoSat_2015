#pragma once
#include "EventAction.h"
#include "Adafruit_BMP085_U.h"
#include "RTClib.h"
#include "EventData.h"
class arduino_mega;

CREATE_EVENT_TRIGGERING_ACTION_2ARGS(doorman_altitude_check, DOOR_DATA, Adafruit_BMP085_Unified bmp, arduino_mega* arduino)
	Adafruit_BMP085_Unified _bmp;
	arduino_mega* _arduino;
	END_CREATE

CREATE_EVENT_TRIGGERING_ACTION(doorman_open, DoorOpen_Data)

DateTime _doorOpenStart;
DateTime _doorOpenFinish;

END_CREATE

CREATE_EVENT_TRIGGERING_ACTION(doorman_close, DoorClose_Data)

DateTime _doorCloseStart;
DateTime _doorCloseFinish;

END_CREATE