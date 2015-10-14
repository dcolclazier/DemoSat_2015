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




struct log_bno_update : public EventAction  {
	log_bno_update(Logger* logger); 
	void execute(EventArgs* args, void* trigger) override;
private:
	File _logfile;
	Logger* _logger;
	String _filename;
};

struct log_bmp_update : public EventAction  {
	log_bmp_update(Logger* logger); 
	void execute(EventArgs* args, void* trigger) override;
private:
	File _logfile;
	Logger* _logger;
	String _filename;
};

