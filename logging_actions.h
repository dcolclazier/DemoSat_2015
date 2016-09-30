#pragma once
#include "WString.h"
#include "EventHandler.h"
#include <SD.h>
#include "sd_shield.h"
//This action gets a little more complex, in that it needs something 
//from somewhere else in the program. In this case, it needs a reference
//to the SD Shield, so that it can perform its task of logging the data from
//the BNO orientation sensors

struct log_bno_update : public EventAction { 
	log_bno_update(SD_Shield* logger); 
	void execute(EventArgs* args, void* trigger) override; private: ;

	File _logfile;
	SD_Shield* _logger;
	String _filename;
};

struct log_altitude_update : public EventAction { log_altitude_update(SD_Shield* logger); void execute(EventArgs* args, void* trigger) override; private: ;

File _logfile;
SD_Shield* _logger;
String _filename;
};

struct log_ext_temp : public EventAction { log_ext_temp(SD_Shield* logger); void execute(EventArgs* args, void* trigger) override; private: ;

File _logfile;
SD_Shield* _logger;
String _filename;
};
