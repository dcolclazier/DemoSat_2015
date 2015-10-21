#pragma once
#include "EventAction.h"
#include "Adafruit_BNO055.h"
#include "Adafruit_BMP085_U.h"
#include "EventArgs.h"
CREATE_EVENT_TRIGGERING_ACTION_1ARG(doorman_altitude_check, DOOR_DATA, Adafruit_BMP085_Unified bmp)
Adafruit_BMP085_Unified _bmp;
END_CREATE
	
