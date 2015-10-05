#include "Logger.h"
#include "RTClib.h"
#include "RedBoard.h"
#include "EventHandler.h"

Logger::Logger(RedBoard* redboard) : _redboard(redboard){
	pinMode(SS, OUTPUT);
	while (!_card.init(SPI_HALF_SPEED, 10,11,12,13)) {
		Serial.println(F("Something went wrong with the SD Card init..."));
	}
	if (!_volume.init(_card)) {
		Serial.println(F("Couldn't find FAT16/FAT32 partition..."));
		return;
	}
	SD.begin(10,11,12,13);

}

DateTime Logger::getTime() {
	return _redboard->getTime();
}

UNARYACTIONSETUP(log_bno_update, Logger* logger) : _logger(logger) {
	char filename[] = "BNO00.CSV";
	for (uint8_t i = 0; i < 100; i++) {
		filename[3] = i / 10 + '0';
		filename[4] = i % 10 + '0';
		if (!SD.exists(filename)) {
			// only open a new file if it doesn't exist
			_logfile = SD.open(filename, O_CREAT | O_WRITE);
			_filename = filename;
			Serial.println(_filename);
			break;  // leave the loop!
		}
	}
	//print column headers for csv
	_logfile.println(F("millis,datetime,gyro_x,gyro_y,gyro_z,mag_x,mag_y,mag_z,grav_x,grav_y,grav_z,temp_c,accel_x,accel_y,accel_z,euler_x,euler_y,euler_z,quat_x,quat_y,quat_z,quat_w,linear_x,linear_y,linear_z"));
	_logfile.close();

}
ACTIONEXECUTE(log_bno_update) {

	//bno_args * bnoargs = static_cast<bno_args*>(args);
	bno_full_args * bnoargs = static_cast<bno_full_args*>(args);

	_logfile = SD.open(_filename.c_str(), O_CREAT | O_WRITE);
	_logfile.print(millis());
	_logfile.print(F(", "));
	_logfile.print(F("\""));
	DateTime now = _logger->getTime();
	_logfile.print(now.year(), DEC);
	_logfile.print(F("/"));
	_logfile.print(now.month(), DEC);
	_logfile.print(F("/"));
	_logfile.print(now.day(), DEC);
	_logfile.print(F(" "));
	_logfile.print(now.hour(), DEC);
	_logfile.print(F(":"));
	_logfile.print(now.minute(), DEC);
	_logfile.print(F(":"));
	_logfile.print(now.second(), DEC);
	_logfile.print(F("\""));
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Gyro.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Gyro.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Gyro.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Mag.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Mag.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Mag.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Grav.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Grav.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Grav.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Temp, DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Accel.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Accel.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Accel.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Euler.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Euler.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Euler.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Quat.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Quat.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Quat.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->Quat.w(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->linearAccell.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->linearAccell.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->linearAccell.z(), DEC);
	_logfile.println();
	_logfile.close();
}
UNARYACTIONSETUP(log_bmp_update, Logger* logger) : _logger(logger) {
	
	char filename[] = "BMP00.CSV";
	for (uint8_t i = 0; i < 100; i++) {
		filename[3] = i / 10 + '0';
		filename[4] = i % 10 + '0';
		if (!SD.exists(filename)) {
			// only open a new file if it doesn't exist
			_logfile = SD.open(filename, O_CREAT | O_WRITE);
			_filename = filename;
			Serial.println(_filename);
			break;  // leave the loop!
		}
	}
	//print column headers for csv
	_logfile.println(F("millis,datetime,pressure,temp,altitude"));
	_logfile.close();

}
ACTIONEXECUTE(log_bmp_update) {

	//bno_args * bnoargs = static_cast<bno_args*>(args);
	bmp_full_args * bmpargs = static_cast<bmp_full_args*>(args);

	_logfile = SD.open(_filename.c_str(), O_CREAT | O_WRITE);
	_logfile.print(millis());
	_logfile.print(F(", "));
	_logfile.print(F("\""));
	DateTime now = _logger->getTime();
	_logfile.print(now.year(), DEC);
	_logfile.print(F("/"));
	_logfile.print(now.month(), DEC);
	_logfile.print(F("/"));
	_logfile.print(now.day(), DEC);
	_logfile.print(F(" "));
	_logfile.print(now.hour(), DEC);
	_logfile.print(F(":"));
	_logfile.print(now.minute(), DEC);
	_logfile.print(F(":"));
	_logfile.print(now.second(), DEC);
	_logfile.print(F("\""));
	_logfile.print(F(", "));
	_logfile.print(bmpargs->Pressure);
	_logfile.print(F(", "));
	_logfile.print(bmpargs->Temp);
	_logfile.print(F(", "));
	_logfile.print(bmpargs->Altitude);
	_logfile.println();
	_logfile.close();
}