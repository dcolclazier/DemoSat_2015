#include "logging_actions.h"
#include "RTClib.h"

//*************INSTRUCTIONS******************
//Every action gets a setup function and an execute macro.
//Match the name with the action name in sensor_actions.h

//SIMPLE - means that the action won't be triggering any new events, meaning we don't need a type_of_args_sent_with_trigger (see below)
//UNARY - means the action needs one piece of data from somewhere else in the program - could be a sensor, a component, w/e
//BINARY - means the action needs two pieces of data from somewhere else in the program 

// UNARYACTIONSETUP(name_of_action, piece_of_data){
//		put setup code here... if you're going to trigger an event, create that event here. 
//		Also assign your piece_of_data to the private variable you created for it.
// }

// BINARYACTIONSETUP(name_of_action, piece_of_data1, piece_of_data2){
//		put setup code here... if you're going to trigger an event, create that event here. 
//		Also assign your piece_of_data to the private variable you created for it.
// }

// ACTIONEXECUTE(name_of_action){
//		This is the code that runs when the action executes... for example, when the 
//		update_heater_status runs, it checks the average temperature and turns on/off the heater 
//		Another example would be the events below... They respond to a time event triggered in DemoSat.pde
//		and trigger another event containing data from the sensor.

//		One note: the first line of code turns the generic "args" into the args you need - into whatever args are sent with the 
//		event your action is responding to. You can copy/paste from another action until you get used to the syntax.
// }
UNARYACTIONSETUP(log_bno_update, SD_Shield* logger) : _logger(logger) {
	//find a good filename, create the file.
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

	bno_logger_args * bnoargs = static_cast<bno_logger_args*>(args);

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
	_logfile.print(bnoargs->linearAccel.x(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->linearAccel.y(), DEC);
	_logfile.print(F(", "));
	_logfile.print(bnoargs->linearAccel.z(), DEC);
	_logfile.println();
	_logfile.close();
}

UNARYACTIONSETUP(log_altitude_updatepdate, SD_Shield* logger) : _logger(logger) {

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
ACTIONEXECUTE(log_altitude_updatepdate) {

	altitude_args * bmpargs = static_cast<altitude_args*>(args);

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