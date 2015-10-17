#include "sensor_actions.h"
#include "EventHandler.h"
#include <Adafruit_BMP085_U.h>
//*************INSTRUCTIONS******************
//Every action gets a setup function and an execute macro.
//Match the name with the action name in sensor_actions.h

//SIMPLE - means that the action won't be triggering any new events, meaning we don't need a type_of_args_sent_with_trigger (see below)
//UNARY - means the action needs one piece of data from somewhere else in the program - could be a sensor, a component, w/e
//BINARY - means the action needs two pieces of data from somewhere else in the program 

// SETUP_TRIGGERACTION_ONE_ARG(name_of_action, piece_of_data){
//		put setup code here... if you're going to trigger an event, create that event here. 
//		Also assign your piece_of_data to the private variable you created for it.
// }

// SETUP_TRIGGERACTION_TWO_ARGS(name_of_action, piece_of_data1, piece_of_data2){
//		put setup code here... if you're going to trigger an event, create that event here. 
//		Also assign your piece_of_data to the private variable you created for it.
// }

// EXECUTE_ACTION(name_of_action){
//		This is the code that runs when the action executes... for example, when the 
//		update_heater_status runs, it checks the average temperature and turns on/off the heater 
//		Another example would be the events below... They respond to a time event triggered in DemoSat.pde
//		and trigger another event containing data from the sensor.

//		One note: the first line of code turns the generic "args" into the args you need - into whatever args are sent with the 
//		event your action is responding to. You can copy/paste from another action until you get used to the syntax.
// }

//BNO055 GYROSCOPE UPDATE - to trigger, use event name "gyro_update"
//args should be casted into a gyro_args
//args contains gyroscope data
SETUP_TRIGGERACTION_ONE_ARG(gyro_update, Adafruit_BNO055 bno)  {
	_bno = bno;
	EVENTHANDLER.add_event("gyro_update");
}
EXECUTE_ACTION(gyro_update) {

	_args.Gyro = _bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
	EVENTHANDLER.trigger("gyro_update", &_args);
}

//BNO055 MAGNETOMETER UPDATE - to trigger, use event name "magnetometer_update"
//args should be casted into a magnetometer_args
//args contain magnetometer data
SETUP_TRIGGERACTION_ONE_ARG(magnetometer_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("magnetometer_update");
}
EXECUTE_ACTION(magnetometer_update) {

	_args.Mag = _bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
	EVENTHANDLER.trigger("magnetometer_update", &_args);
}

//BNO055 GRAVITOMETER UPDATE - to trigger, use event name "gravitometer_update"
//args should be casted into a gravitometer_args
//args contain gravitometer data
SETUP_TRIGGERACTION_ONE_ARG(gravitometer_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("gravitometer_update");
}
EXECUTE_ACTION(gravitometer_update) {

	_args.Grav = _bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
	EVENTHANDLER.trigger("gravitometer_update", &_args);
}

//BNO055 ACCELERATION UPDATE - to trigger, use event name "accelerometer_update"
//args should be casted into a accelerometer_args
//args contain accelerometer and linear acceleration
SETUP_TRIGGERACTION_ONE_ARG(accelerometer_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("accelerometer_update");
}
EXECUTE_ACTION(accelerometer_update) {

	_args.Accel = _bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
	_args.linearAccel = _bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
	EVENTHANDLER.trigger("accelerometer_update", &_args);
}

//BNO055 POSITION UPDATE - to trigger, use event name "position_update"
//args should be casted into a position_args
//args contains both euler heading and quaternion
SETUP_TRIGGERACTION_ONE_ARG(position_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("position_update");
}
EXECUTE_ACTION(position_update) {

	_args.Euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	_args.Quat = _bno.getQuat();
	EVENTHANDLER.trigger("position_update", &_args);
}

//BNO055 Full UPDATE - to trigger, use event name "bno_logger_update"
//args should be casted into a bno_logger_args
//args contains all possible data from bno_055 sensor 
//use this for logging data - it's memory intensive.
SETUP_TRIGGERACTION_ONE_ARG(bno_logger_update, Adafruit_BNO055 bno)  {
	_bno = bno;
	EVENTHANDLER.add_event("bno_logger_update");
}
EXECUTE_ACTION(bno_logger_update) {

	_args.Gyro = _bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
	_args.Mag = _bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
	_args.Grav = _bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
	_args.Temp = _bno.getTemp();
	_args.Accel = _bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
	_args.Euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	_args.Quat = _bno.getQuat();
	_args.linearAccel = _bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
	EVENTHANDLER.trigger("bno_logger_update", &_args);
}

//BMP SENSOR UPDATE - to trigger, use event name "altitude_update"
//args should be casted into a altitude_args
//args contains temperature, pressure and altitude
SETUP_TRIGGERACTION_ONE_ARG(altitude_update, Adafruit_BMP085_Unified bmp) {
	_bmp = bmp;
	EVENTHANDLER.add_event("altitude_update");
}
EXECUTE_ACTION(altitude_update) {
	sensors_event_t event;
	_bmp.getEvent(&event);
	_args.Pressure = event.pressure;
	_bmp.getTemperature(&_args.Temp);
	_args.Altitude = _bmp.pressureToAltitude(_seaLevelPressure, event.pressure, _args.Temp);
	EVENTHANDLER.trigger("altitude_update", &_args);
}

//AVG TEMP UPDATE - to trigger, use event name "avg_tmp"
//args should be casted into a temperature_args
//args contains temperature, pressure and altitude
SETUP_TRIGGERACTION_TWO_ARGS(avg_temp_update, Adafruit_BMP085_Unified bmp, Adafruit_BNO055 bno)
	: _bmp(bmp), _bno(bno) {
	EVENTHANDLER.add_event("avg_temp_update");
}
EXECUTE_ACTION(avg_temp_update) {
	_bmp.getTemperature(&_args.BMP_Temp);
	_args.BNO_Temp = _bno.getTemp();
	_args.avg_temp_update = (_args.BNO_Temp + _args.BMP_Temp) / 2;
	EVENTHANDLER.trigger("avg_temp_update", &_args);
}
