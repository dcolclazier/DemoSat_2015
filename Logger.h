#pragma once
#include <Arduino.h>
#include "SD.h"
#include "EventHandler.h"
class DateTime;
class Mega2560;
class Logger {
public:

	explicit Logger(Mega2560* redboard);
	DateTime getTime();

private:
	Mega2560* _redboard;
	const byte chipSelect = 4;
	Sd2Card _card;
	SdVolume _volume;
	SdFile _root;
		
};

//if we have a buffer, we should probably have a 2d array with the data..
//every time we add an entry, update the size for the array
//when the size of the array hits 512, send it to the logger
//here's one issue:
//   we may need more than one buffer - one buffer for each file, so we need a file buffer class
//   that holds on to the filename.. or rather a file wrapper that holds onto a buffer - that.

struct file_wrapper {

	int _columns = 22;

	uint8_t(* buffer_array)[12];

	file_wrapper() { buffer_array = new uint8_t[_columns][12]; }

	void flush() {
		auto to_flush = buffer_array;
		_logfile = SD.open(_filename, O_CREAT | O_WRITE);
		for (auto x = 0; x < column_count; x++) {
			for (auto y = 0; y < current_row; y++) {
				_logfile.print(buffer_array[x][y]);
				_logfile.print(F(","));
			}
		}
	}

	template<typename T>
	void add_to_buffer(T to_add) {
		if(current_size + sizeof(T) < max_buffer_size) {
			buffer_array[++current_column][current_row] = to_add;
			current_size += sizeof(T);
			if (current_column == column_count) current_row++;
		}
		else{
			flush();
		}
	}

	File _logfile;
	char* _filename;
	Logger* _logger;
//private:
	int max_buffer_size = 1024;
	int current_row = 0;
	int current_column = 0;
	int current_size = 0;
	int column_count;
	 
};

struct better_log_bno_update : public EventAction {

	better_log_bno_update(Logger* logger);

	void execute(EventArgs* args, void* trigger) override;

	file_wrapper buffer_test;
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

