#include "logging_actions.h"
#include "RTClib.h"
#include <avr\pgmspace.h>


SETUP_ACTION_1ARG(log_all_data,const SD_Shield& logger)
{
	Serial.println("starting file check...");
	char filename[] = "DATA00.CSV";
	for (uint8_t i = 0; i < 100; i++) {
		filename[4] = i / 10 + '0';
		filename[5] = i % 10 + '0';
		if (!SD.exists(filename)) {
			// only open a new file if it doesn't exist
			_logfile = SD.open(filename, O_CREAT | O_WRITE);
			_filename = filename;
			Serial.println(_filename);
			break;  // leave the loop!
		}
	}
	//pressure, temp, altitude, ext_temp
	_logfile.println(F("millis,datetime,calib_system,calib_gyro,calib_accel,calib_mag,gyro_x,gyro_y,gyro_z,mag_x,mag_y,mag_z,grav_x,grav_y,grav_z,temp_c,accel_x,accel_y,accel_z,euler_x,euler_y,euler_z,quat_x,quat_y,quat_z,quat_w,linear_x,linear_y,linear_z,pressure,bmp_temp,altitude,external_temp,rel_humid,humid_temp,IR,Visible"));
	_logfile.close();
}
EXECUTE_ACTION(log_all_data)
{
	//sensor_data* data = static_cast<sensor_data*>(args);
	new_sensor_data* data = static_cast<new_sensor_data*>(args);
	
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
	_logfile.print(data->calib_fusion);
	_logfile.print(F(", "));
	_logfile.print(data->calib_gyro);
	_logfile.print(F(", "));
	_logfile.print(data->calib_accel);
	_logfile.print(F(", "));
	_logfile.print(data->calib_mag);
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
	_logfile.print(F(", "));
	_logfile.print(data->Rel_Humidity);
	_logfile.print(F(", "));
	_logfile.print(data->Humid_Temp);
	_logfile.print(F(", "));
	_logfile.print(data->IR);
	_logfile.print(F(", "));
	_logfile.print(data->visible);
	_logfile.println();
	_logfile.close();
}

SETUP_ACTION_1ARG(log_door_data, const SD_Shield& logger) {
	Serial.println("starting file check...");
	char filename[] = "DOOR00.txt";
	for (uint8_t i = 0; i < 100; i++) {
		filename[4] = i / 10 + '0';
		filename[5] = i % 10 + '0';
		if (!SD.exists(filename)) {
			// only open a new file if it doesn't exist
			_logfile = SD.open(filename, O_CREAT | O_WRITE);
			_filename = filename;
			Serial.println(_filename);
			break;  // leave the loop!
		}
	}

	_logfile.close();
}
EXECUTE_ACTION(log_door_data) {
	Door_Data* door = static_cast<Door_Data*>(args);

	_logfile = SD.open(_filename.c_str(), O_CREAT | O_WRITE);
	Serial.print("DOOR ");
	Serial.print(door->door_number);
	Serial.println(" OPEN START: ");
	Serial.print(F("\""));
	Serial.print(door->door_open_start.year(), DEC);
	Serial.print(F("/"));
	Serial.print(door->door_open_start.month(), DEC);
	Serial.print(F("/"));
	Serial.print(door->door_open_start.day(), DEC);
	Serial.print(F(" "));
	Serial.print(door->door_open_start.hour(), DEC);
	Serial.print(F(":"));
	Serial.print(door->door_open_start.minute(), DEC);
	Serial.print(F(":"));
	Serial.print(door->door_open_start.second(), DEC);
	Serial.print(F("\""));
	Serial.println();
	Serial.print("DOOR OPEN FINISH: ");
	Serial.print(F("\""));
	Serial.print(door->door_open_finish.year(), DEC);
	Serial.print(F("/"));
	Serial.print(door->door_open_finish.month(), DEC);
	Serial.print(F("/"));
	Serial.print(door->door_open_finish.day(), DEC);
	Serial.print(F(" "));
	Serial.print(door->door_open_finish.hour(), DEC);
	Serial.print(F(":"));
	Serial.print(door->door_open_finish.minute(), DEC);
	Serial.print(F(":"));
	Serial.print(door->door_open_finish.second(), DEC);
	Serial.print(F("\""));
}