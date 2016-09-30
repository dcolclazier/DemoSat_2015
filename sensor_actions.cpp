#include "sensor_actions.h"
#include "EventHandler.h"
#include <Adafruit_BMP085_U.h>
#include <Adafruit_BNO055.h>

//BNO055 GYROSCOPE UPDATE - to trigger, use event name "gyro_update"
//args should be casted into a gyro_data
//args contains gyroscope data
gyro_update::gyro_update(Adafruit_BNO055 bno)  {
	_bno = bno;
	EventHandler::instance().add_event("gyro_update");
}
void gyro_update::execute(EventArgs* args, void* trigger) {

	_args.Gyro = _bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
	EventHandler::instance().trigger("gyro_update", &_args);
}

//BNO055 MAGNETOMETER UPDATE - to trigger, use event name "magnetometer_update"
//args should be casted into a magnetometer_args
//args contain magnetometer data
magnetometer_update::magnetometer_update(Adafruit_BNO055 bno) {
	_bno = bno;
	EventHandler::instance().add_event("magnetometer_update");
}
void magnetometer_update::execute(EventArgs* args, void* trigger) {

	_args.Mag = _bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
	EventHandler::instance().trigger("magnetometer_update", &_args);
}

//BNO055 GRAVITOMETER UPDATE - to trigger, use event name "gravitometer_update"
//args should be casted into a gravitometer_args
//args contain gravitometer data
gravitometer_update::gravitometer_update(Adafruit_BNO055 bno) {
	_bno = bno;
	EventHandler::instance().add_event("gravitometer_update");
}
void gravitometer_update::execute(EventArgs* args, void* trigger) {

	_args.Grav = _bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
	EventHandler::instance().trigger("gravitometer_update", &_args);
}

//BNO055 ACCELERATION UPDATE - to trigger, use event name "accelerometer_update"
//args should be casted into a accelerometer_args
//args contain accelerometer and linear acceleration
accelerometer_update::accelerometer_update(Adafruit_BNO055 bno) {
	_bno = bno;
	EventHandler::instance().add_event("accelerometer_update");
}
void accelerometer_update::execute(EventArgs* args, void* trigger) {

	_args.Accel = _bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
	_args.linearAccel = _bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
	EventHandler::instance().trigger("accelerometer_update", &_args);
}

//BNO055 POSITION UPDATE - to trigger, use event name "position_update"
//args should be casted into a position_args
//args contains both euler heading and quaternion
position_update::position_update(Adafruit_BNO055 bno) {
	_bno = bno;
	EventHandler::instance().add_event("position_update");
}
void position_update::execute(EventArgs* args, void* trigger) {

	_args.Euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	_args.Quat = _bno.getQuat();
	EventHandler::instance().trigger("position_update", &_args);
}

//BNO055 Full UPDATE - to trigger, use event name "bno_logger_update"
//args should be casted into a bno_logger_data
//args contains all possible data from bno_055 sensors 
//use this for logging data - it's memory intensive.
bno_logger_update::bno_logger_update(Adafruit_BNO055 bno)  {
	_bno = bno;
	EventHandler::instance().add_event("bno_logger_update");
}
void bno_logger_update::execute(EventArgs* args, void* trigger) {

	_args.Gyro = _bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
	_args.Mag = _bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
	_args.Grav = _bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
	_args.Temp = _bno.getTemp();
	_args.Accel = _bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
	_args.Euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	_args.Quat = _bno.getQuat();
	_args.linearAccel = _bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
	EventHandler::instance().trigger("bno_logger_update", &_args);
}

//BMP SENSOR UPDATE - to trigger, use event name "altitude_update"
//args should be casted into a altitude_args
//args contains temperature, pressure and altitude
altitude_update::altitude_update(Adafruit_BMP085_Unified bmp) :_bmp(bmp) {

	EventHandler::instance().add_event("altitude_update");
}
void altitude_update::execute(EventArgs* args, void* trigger) {
	sensors_event_t event;
	_bmp.getEvent(&event);
	_args.Pressure = event.pressure;
	_bmp.getTemperature(&_args.Temp);
	_args.Altitude = _bmp.pressureToAltitude(_seaLevelPressure, event.pressure, _args.Temp);
	EventHandler::instance().trigger("altitude_update", &_args);
}

//AVG TEMP UPDATE - to trigger, use event name "avg_tmp"
//args should be casted into a temperature_args
//args contains temperature, pressure and altitude
avg_temp_update::avg_temp_update(Adafruit_BMP085_Unified bmp, Adafruit_BNO055 bno)
	: _bmp(bmp), _bno(bno) {
	EventHandler::instance().add_event("avg_temp_update");
}
void avg_temp_update::execute(EventArgs* args, void* trigger) {
	_bmp.getTemperature(&_args.BMP_Temp);
	_args.BNO_Temp = _bno.getTemp();
	_args.AVG_temp = (_args.BNO_Temp + _args.BMP_Temp) / 2;
	EventHandler::instance().trigger("avg_temp_update", &_args);
}
