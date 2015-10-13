#pragma once
#include <Arduino.h>
#include "SD.h"
#include "EventHandler.h"
class DateTime;
class RedBoard;
class Logger {
public:

	explicit Logger(RedBoard* redboard);
	DateTime getTime();

private:
	RedBoard* _redboard;
	const byte chipSelect = 4;
	Sd2Card _card;
	SdVolume _volume;
	SdFile _root;
		
};




ACTION(log_bno_update) {
	UNARYACTIONINIT(log_bno_update, Logger* logger);
private:
	File _logfile;
	Logger* _logger;
	String _filename;
};

ACTION(log_bmp_update) {
	UNARYACTIONINIT(log_bmp_update, Logger* logger);
private:
	File _logfile;
	Logger* _logger;
	String _filename;
};

