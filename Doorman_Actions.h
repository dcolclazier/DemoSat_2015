#pragma once
#include "EventAction.h"
#include "Adafruit_BMP085_U.h"
#include "EventData.h"
CREATE_EVENT_TRIGGERING_ACTION_1ARG(doorman_altitude_check, DOOR_DATA, Adafruit_BMP085_Unified bmp)
	Adafruit_BMP085_Unified _bmp;
END_CREATE

CREATE_EVENT_TRIGGERING_ACTION(doorman_open, DoorOpen_Data)

Time _doorOpenStart;
Time _doorOpenFinish;

END_CREATE

CREATE_EVENT_TRIGGERING_ACTION(doorman_close, DoorOpen_Data)

Time _doorCloseStart;
Time _doorCloseFinish;

END_CREATE