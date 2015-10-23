#pragma once
#include "WString.h"
#include "EventHandler.h"
#include <SD.h>
#include "sd_shield.h"


CREATE_ACTION_1ARG(log_all_data, const SD_Shield& logger)
File _logfile;
SD_Shield* _logger;
String _filename;
END_CREATE

CREATE_ACTION_1ARG(log_door_data, const SD_Shield& logger)
	File _logfile;
	SD_Shield* _logger;
	String _filename;

END_CREATE

