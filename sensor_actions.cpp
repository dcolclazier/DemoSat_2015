#include "sensor_actions.h"
#include "EventHandler.h"
#include <Adafruit_BMP085_U.h>
//*************INSTRUCTIONS******************
//Every action gets a setup function and an execute macro.
//Match the name with the action name in sensor_actions.h

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
//		and trigger another event containing data from the sensors.

//		One note: the first line of code turns the generic "args" into the args you need - into whatever args are sent with the 
//		event your action is responding to. You can copy/paste from another action until you get used to the syntax.
// }


SETUP_ACTION_4ARGS(sensor_update, Adafruit_BNO055 bno, Adafruit_BMP085_Unified bmp, DallasTemperature sensor, HIH6130 humid_sensor)
	: _bno(bno), _bmp(bmp), _extTemp(sensor), _humidSensor(humid_sensor)
{
	EVENTHANDLER.add_event("sensor_update");
}
EXECUTE_ACTION(sensor_update)
{
	sensors_event_t bmp_event;
	sensors_event_t bno_event;
	_bmp.getEvent(&bmp_event);
	_bno.getEvent(&bno_event);

	_args.Accel = _bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
	_args.Pressure = bmp_event.pressure;
	_bmp.getTemperature(&_args.bmp_Temp);
	_args.Altitude = _bmp.pressureToAltitude(_seaLevelPressure, bmp_event.pressure, _args.bmp_Temp);
	_args.Euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	_args.Grav = _bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
	_args.Gyro = _bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
	_args.Quat = _bno.getQuat();
	_args.linearAccel = _bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
	_args.Mag = _bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
	_args.bno_Temp = _bno.getTemp();
	_args.ext_Temp = _extTemp.getTempC(0);
		
	EVENTHANDLER.trigger("sensor_update", &_args);

}

SETUP_ACTION(get_external_temp) : oneWireBus(OneWire(2)), sensors(&oneWireBus) {
	EVENTHANDLER.add_event("external_temp_update");
	//sensors.begin();//Turn on all sensors on IC bus
}

EXECUTE_ACTION(get_external_temp) {

	sensors.requestTemperatures();//Request reading from probe
	_args.EXT_Temp = sensors.getTempCByIndex(0);
	EVENTHANDLER.trigger("external_temp_update", &_args);
}


//BNO055 MAGNETOMETER UPDATE - to trigger, use event name "magnetometer_update"
//args should be casted into a magnetometer_args
//args contain magnetometer data
SETUP_ACTION_ONE_ARG(magnetometer_update, Adafruit_BNO055 bno) {
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
SETUP_ACTION_ONE_ARG(gravitometer_update, Adafruit_BNO055 bno) {
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
SETUP_ACTION_ONE_ARG(accelerometer_update, Adafruit_BNO055 bno) {
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
SETUP_ACTION_ONE_ARG(position_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("position_update");
}
EXECUTE_ACTION(position_update) {

	_args.Euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	_args.Quat = _bno.getQuat();
	EVENTHANDLER.trigger("position_update", &_args);
}

//BNO055 Full UPDATE - to trigger, use event name "bno_logger_update"
//args should be casted into a bno_logger_data
//args contains all possible data from bno_055 sensors 
//use this for logging data - it's memory intensive.
SETUP_ACTION_ONE_ARG(bno_logger_update, Adafruit_BNO055 bno)  {
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
SETUP_ACTION_ONE_ARG(altitude_update, Adafruit_BMP085_Unified bmp) :_bmp(bmp) {

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
SETUP_ACTION_TWO_ARGS(avg_temp_update, Adafruit_BMP085_Unified bmp, Adafruit_BNO055 bno)
	: _bmp(bmp), _bno(bno) {
	EVENTHANDLER.add_event("avg_temp_update");
}
EXECUTE_ACTION(avg_temp_update) {
	_bmp.getTemperature(&_args.BMP_Temp);
	_args.BNO_Temp = _bno.getTemp();
	_args.AVG_temp = (_args.BNO_Temp + _args.BMP_Temp) / 2;
	EVENTHANDLER.trigger("avg_temp_update", &_args);
}
