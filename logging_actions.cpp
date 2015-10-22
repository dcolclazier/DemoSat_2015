#include "logging_actions.h"
#include "RTClib.h"

//SETUP_ACTION_ONE_ARG(log_bno_update, SD_Shield* logger) : _logger(logger) {
//	//find a good filename, create the file.
//	char filename[] = "BNO00.CSV";
//	for (uint8_t i = 0; i < 100; i++) {
//		filename[3] = i / 10 + '0';
//		filename[4] = i % 10 + '0';
//		if (!SD.exists(filename)) {
//			// only open a new file if it doesn't exist
//			_logfile = SD.open(filename, O_CREAT | O_WRITE);
//			_filename = filename;
//			Serial.println(_filename);
//			break;  // leave the loop!
//		}
//	}
//	//print column headers for csv
//	_logfile.println(F("millis,datetime,gyro_x,gyro_y,gyro_z,mag_x,mag_y,mag_z,grav_x,grav_y,grav_z,temp_c,accel_x,accel_y,accel_z,euler_x,euler_y,euler_z,quat_x,quat_y,quat_z,quat_w,linear_x,linear_y,linear_z"));
//	_logfile.close();
//
//}
//EXECUTE_ACTION(log_bno_update) {
//
//	bno_logger_data * bnoargs = static_cast<bno_logger_data*>(args);
//
//	_logfile = SD.open(_filename.c_str(), O_CREAT | O_WRITE);
//	_logfile.print(millis());
//	_logfile.print(F(", "));
//	_logfile.print(F("\""));
//	DateTime now = _logger->getTime();
//	_logfile.print(now.year(), DEC);
//	_logfile.print(F("/"));
//	_logfile.print(now.month(), DEC);
//	_logfile.print(F("/"));
//	_logfile.print(now.day(), DEC);
//	_logfile.print(F(" "));
//	_logfile.print(now.hour(), DEC);
//	_logfile.print(F(":"));
//	_logfile.print(now.minute(), DEC);
//	_logfile.print(F(":"));
//	_logfile.print(now.second(), DEC);
//	_logfile.print(F("\""));
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Gyro.x(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Gyro.y(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Gyro.z(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Mag.x(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Mag.y(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Mag.z(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Grav.x(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Grav.y(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Grav.z(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Temp, DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Accel.x(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Accel.y(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Accel.z(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Euler.x(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Euler.y(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Euler.z(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Quat.x(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Quat.y(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Quat.z(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->Quat.w(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->linearAccel.x(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->linearAccel.y(), DEC);
//	_logfile.print(F(", "));
//	_logfile.print(bnoargs->linearAccel.z(), DEC);
//	_logfile.println();
//	_logfile.close();
//}
//
//SETUP_ACTION_ONE_ARG(log_altitude_update, SD_Shield* logger) : _logger(logger) {
//
//	char filename[] = "BMP00.CSV";
//	for (uint8_t i = 0; i < 100; i++) {
//		filename[3] = i / 10 + '0';
//		filename[4] = i % 10 + '0';
//		if (!SD.exists(filename)) {
//			// only open a new file if it doesn't exist
//			_logfile = SD.open(filename, O_CREAT | O_WRITE);
//			_filename = filename;
//			Serial.println(_filename);
//			break;  // leave the loop!
//		}
//	}
//	//print column headers for csv
//	_logfile.println(F("millis,datetime,pressure,temp,altitude"));
//	_logfile.close();
//
//}
//EXECUTE_ACTION(log_altitude_update) {
//
//	altitude_args * bmpargs = static_cast<altitude_args*>(args);
//
//	_logfile = SD.open(_filename.c_str(), O_CREAT | O_WRITE);
//	_logfile.print(millis());
//	_logfile.print(F(", "));
//	_logfile.print(F("\""));
//	DateTime now = _logger->getTime();
//	_logfile.print(now.year(), DEC);
//	_logfile.print(F("/"));
//	_logfile.print(now.month(), DEC);
//	_logfile.print(F("/"));
//	_logfile.print(now.day(), DEC);
//	_logfile.print(F(" "));
//	_logfile.print(now.hour(), DEC);
//	_logfile.print(F(":"));
//	_logfile.print(now.minute(), DEC);
//	_logfile.print(F(":"));
//	_logfile.print(now.second(), DEC);
//	_logfile.print(F("\""));
//	_logfile.print(F(", "));
//	_logfile.print(bmpargs->Pressure);
//	_logfile.print(F(", "));
//	_logfile.print(bmpargs->Temp);
//	_logfile.print(F(", "));
//	_logfile.print(bmpargs->Altitude);
//	_logfile.println();
//	_logfile.close();
//}
//
//SETUP_ACTION_ONE_ARG(log_ext_temp, SD_Shield* logger) : _logger(logger) {
//
//	char filename[] = "EXT_TMP00.CSV";
//	for (uint8_t i = 0; i < 100; i++) {
//		filename[3] = i / 10 + '0';
//		filename[4] = i % 10 + '0';
//		if (!SD.exists(filename)) {
//			// only open a new file if it doesn't exist
//			_logfile = SD.open(filename, O_CREAT | O_WRITE);
//			_filename = filename;
//			Serial.println(_filename);
//			break;  // leave the loop!
//		}
//	}
//	//print column headers for csv
//	_logfile.println(F("Time,Datestamp,External Temp"));
//	_logfile.close();
//
//}
//EXECUTE_ACTION(log_ext_temp) {
//
//	externalTemp_args * tmpargs = static_cast<externalTemp_args*>(args);
//
//	_logfile = SD.open(_filename.c_str(), O_CREAT | O_WRITE);
//	_logfile.print(millis());
//	_logfile.print(F(", "));
//	_logfile.print(F("\""));
//	DateTime now = _logger->getTime();
//	_logfile.print(now.year(), DEC);
//	_logfile.print(F("/"));
//	_logfile.print(now.month(), DEC);
//	_logfile.print(F("/"));
//	_logfile.print(now.day(), DEC);
//	_logfile.print(F(" "));
//	_logfile.print(now.hour(), DEC);
//	_logfile.print(F(":"));
//	_logfile.print(now.minute(), DEC);
//	_logfile.print(F(":"));
//	_logfile.print(now.second(), DEC);
//	_logfile.print(F("\""));
//	_logfile.print(F(", "));
//	_logfile.print(tmpargs->EXT_Temp);
//	_logfile.println();
//	_logfile.close();
//}

SETUP_ACTION_ONE_ARG(log_all_data, SD_Shield* logger)
{
	char filename[] = "DATA00.CSV";
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
	//pressure, temp, altitude, ext_temp
	_logfile.println(F("millis,datetime,gyro_x,gyro_y,gyro_z,mag_x,mag_y,mag_z,grav_x,grav_y,grav_z,temp_c,accel_x,accel_y,accel_z,euler_x,euler_y,euler_z,quat_x,quat_y,quat_z,quat_w,linear_x,linear_y,linear_z,pressure,bmp_temp,altitude,external_temp"));
	_logfile.close();
}
EXECUTE_ACTION(log_all_data)
{
	sensor_data* data = static_cast<sensor_data*>(args);
	Serial.print(_filename.c_str());
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
	_logfile.print(data->Gyro.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Gyro.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Gyro.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Mag.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Mag.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Mag.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Grav.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Grav.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Grav.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->bno_Temp, DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Accel.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Accel.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Accel.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Euler.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Euler.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Euler.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Quat.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Quat.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Quat.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Quat.w(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->linearAccel.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->linearAccel.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->linearAccel.z(), DEC);
	_logfile.print(F(", "));
	_logfile.print(data->Pressure);
	_logfile.print(F(", "));
	_logfile.print(data->bmp_Temp);
	_logfile.print(F(", "));
	_logfile.print(data->Altitude);
	_logfile.print(F(", "));
	_logfile.print(data->ext_Temp);
	_logfile.println();

}