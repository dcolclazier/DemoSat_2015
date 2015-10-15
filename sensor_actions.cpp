#include "sensor_actions.h"
#include "EventHandler.h"
#include <Adafruit_BMP085_U.h>
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

//BNO055 GYROSCOPE UPDATE - to trigger, use event name "bn_gy_u"
//args should be casted into a bno_gyro_args
//args contains gyroscope data
UNARYACTIONSETUP(bno_gyro_update, Adafruit_BNO055 bno)  {
	_bno = bno;
	EVENTHANDLER.add_event("bn_gy_u", new Event);
}
ACTIONEXECUTE(bno_gyro_update) {

	_args.Gyro = _bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
	EVENTHANDLER.trigger("bn_gy_u", &_args, &_bno);
}

//BNO055 MAGNETOMETER UPDATE - to trigger, use event name "bn_m_u"
//args should be casted into a bno_mag_args
//args contain magnetometer data
UNARYACTIONSETUP(bno_mag_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("bn_m_u", new Event);
}
ACTIONEXECUTE(bno_mag_update) {

	_args.Mag = _bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
	EVENTHANDLER.trigger("bn_m_u", &_args, &_bno);
}

//BNO055 GRAVITOMETER UPDATE - to trigger, use event name "bn_gr_u"
//args should be casted into a bno_grav_args
//args contain gravitometer data
UNARYACTIONSETUP(bno_grav_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("bn_gr_u", new Event);
}
ACTIONEXECUTE(bno_grav_update) {

	_args.Grav = _bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
	EVENTHANDLER.trigger("bn_gr_u", &_args, &_bno);
}

//BNO055 ACCELERATION UPDATE - to trigger, use event name "bn_a_u"
//args should be casted into a bno_accel_args
//args contain accelerometer and linear acceleration
UNARYACTIONSETUP(bno_accel_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("bn_a_u", new Event);
}
ACTIONEXECUTE(bno_accel_update) {

	_args.Accel = _bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
	_args.linearAccel = _bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
	EVENTHANDLER.trigger("bn_a_u", &_args, &_bno);
}

//BNO055 POSITION UPDATE - to trigger, use event name "bn_p_u"
//args should be casted into a bno_position_args
//args contains both euler heading and quaternion
UNARYACTIONSETUP(bno_position_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("bn_p_u", new Event);
}
ACTIONEXECUTE(bno_position_update) {

	_args.Euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	_args.Quat = _bno.getQuat();
	EVENTHANDLER.trigger("bn_p_u", &_args, &_bno);
}

//BNO055 Full UPDATE - to trigger, use event name "bn_full_u"
//args should be casted into a bno_full_args
//args contains all possible data from bno_055 sensor 
//use this for logging data - it's memory intensive.
UNARYACTIONSETUP(bno_full_update, Adafruit_BNO055 bno)  {
	_bno = bno;
	EVENTHANDLER.add_event("bn_full_u", new Event);
}
ACTIONEXECUTE(bno_full_update) {

	_args.Gyro = _bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
	_args.Mag = _bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
	_args.Grav = _bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
	_args.Temp = _bno.getTemp();
	_args.Accel = _bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
	_args.Euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	_args.Quat = _bno.getQuat();
	_args.linearAccel = _bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
	EVENTHANDLER.trigger("bn_full_u", &_args, &_bno);
}

//BMP SENSOR UPDATE - to trigger, use event name "alt_u"
//args should be casted into a bmp_full_args
//args contains temperature, pressure and altitude
UNARYACTIONSETUP(altitude_sensor_update, Adafruit_BMP085_Unified bmp) {
	_bmp = bmp;
	EVENTHANDLER.add_event("alt_u", new Event);
}
ACTIONEXECUTE(altitude_sensor_update) {
	sensors_event_t event;
	_bmp.getEvent(&event);
	_args.Pressure = event.pressure;
	_bmp.getTemperature(&_args.Temp);
	_args.Altitude = _bmp.pressureToAltitude(_seaLevelPressure, event.pressure, _args.Temp);
	EVENTHANDLER.trigger("alt_u", &_args, &_bmp);
}

//AVG TEMP UPDATE - to trigger, use event name "avg_tmp"
//args should be casted into a avg_temp_args
//args contains temperature, pressure and altitude
BINARYACTIONSETUP(avg_temp_update, Adafruit_BMP085_Unified bmp, Adafruit_BNO055 bno) 
	: _bmp(bmp), _bno(bno) {
	EVENTHANDLER.add_event("avg_temp", new Event);
}
ACTIONEXECUTE(avg_temp_update) {
	_bmp.getTemperature(&_args.BMP_Temp);
	_args.BNO_Temp = _bno.getTemp();
	_args.AVG_Temp = (_args.BNO_Temp + _args.BMP_Temp) / 2;
	EVENTHANDLER.trigger("avg_temp", &_args, 0);
}
