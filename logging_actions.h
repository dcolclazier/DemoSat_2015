#pragma once
#include "WString.h"
#include "EventHandler.h"
#include <SD.h>
#include "sd_shield.h"

//This action gets a little more complex, in that it needs something 
//from somewhere else in the program. In this case, it needs a reference
//to the SD Shield, so that it can perform its task of logging the data from
//the BNO orientation sensors
//CREATE_ACTION_ONE_ARG(log_bno_update, SD_Shield* logger)
//
//File _logfile;
//SD_Shield* _logger;
//String _filename;
//};
//
//CREATE_ACTION_ONE_ARG(log_altitude_update, SD_Shield* logger)
//
//File _logfile;
//SD_Shield* _logger;
//String _filename;
//};
//
//CREATE_ACTION_ONE_ARG(log_ext_temp, SD_Shield* logger)
//
//File _logfile;
//SD_Shield* _logger;
//String _filename;
//};

CREATE_ACTION_ONE_ARG(log_all_data, SD_Shield* logger)
File _logfile;
SD_Shield* _logger;
String _filename;
END_CREATE

