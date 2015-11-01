#include "sensor_actions.h"
#include "EventHandler.h"
#include <Adafruit_BMP085_U.h>

//SETUP_ACTION_4ARGS(sensor_update,
//				   const Adafruit_BNO055& bno, 
//				   const Adafruit_BMP085_Unified& bmp, 
//				   const DallasTemperature& sensor, 
//				   const HIH6130& humid_sensor)
//	: _bno(bno), _bmp(bmp), _extTemp(sensor), _humidSensor(humid_sensor)
//{
//	EVENTHANDLER.add_event("sensor_update");
//}
SETUP_ACTION_1ARG(new_sensor_update, const SensorPackage& sensors) : _sensors(sensors)
{
	EVENTHANDLER.add_event("sensor_update");
}

EXECUTE_ACTION(new_sensor_update)
{
	sensors_event_t bmp_event;
	sensors_event_t bno_event;
	_sensors._bmp.getEvent(&bmp_event);
	_sensors._bno.getEvent(&bno_event);

	_args.Accel = _sensors._bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
	_args.Pressure = bmp_event.pressure;
	_sensors._bmp.getTemperature(&_args.bmp_Temp);
	_args.Altitude = _sensors._bmp.pressureToAltitude(_seaLevelPressure, bmp_event.pressure);
	AltitudeData alt_data;
	alt_data.current_alt_in_meters = _args.Altitude;
	EVENTHANDLER.trigger("altitude update", &alt_data);
	_args.Euler = _sensors._bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	_args.Grav = _sensors._bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
	_args.Gyro = _sensors._bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
	_args.Quat = _sensors._bno.getQuat();
	_args.linearAccel = _sensors._bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
	_args.Mag = _sensors._bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
	_args.bno_Temp = _sensors._bno.getTemp();
	_args.ext_Temp = _sensors._extTemp.getTempC(0);

	_sensors._humidSensor.readRHT();
	_args.Rel_Humidity = _sensors._humidSensor.humidity;
	_args.Humid_Temp = _sensors._humidSensor.temperature;

	_sensors._bno.getCalibration(&_args.calib_fusion, &_args.calib_gyro, &_args.calib_accel, &_args.calib_mag);
	config_data data;
	_sensors._bno.getCalibration(&data.calib_system, &data.calib_gyro, &data.calib_accel, &data.calib_mag);
	EVENTHANDLER.trigger("update_config_status", &data);
	_args.IR = _sensors._visibleLight.readIR();
	_args.visible = _sensors._visibleLight.readVisible();
	_args.UltraViolet = _sensors._uvLight.readUV();
	_args.UltraVioletVoltage = _sensors._uvLight.readVoltage();
	EVENTHANDLER.trigger("sensor_update", &_args);
}

//
//EXECUTE_ACTION(sensor_update)
//{
//	sensors_event_t bmp_event;
//	sensors_event_t bno_event;
//	_bmp.getEvent(&bmp_event);
//	_bno.getEvent(&bno_event);
//
//	_args.Accel = _bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
//	_args.Pressure = bmp_event.pressure;
//	_bmp.getTemperature(&_args.bmp_Temp);
//	_args.Altitude = _bmp.pressureToAltitude(_seaLevelPressure, bmp_event.pressure);
//	AltitudeData alt_data;
//	alt_data.current_alt_in_meters = _args.Altitude;
//	EVENTHANDLER.trigger("altitude update", &alt_data);
//	_args.Euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
//	_args.Grav = _bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
//	_args.Gyro = _bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
//	_args.Quat = _bno.getQuat();
//	_args.linearAccel = _bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
//	_args.Mag = _bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
//	_args.bno_Temp = _bno.getTemp();
//	_args.ext_Temp = _extTemp.getTempC(0);
//
//	_humidSensor.readRHT();
//	_args.Rel_Humidity = _humidSensor.humidity;
//	_args.Humid_Temp = _humidSensor.temperature;
//	
//	_bno.getCalibration(&_args.calib_system, &_args.calib_gyro, &_args.calib_accel, &_args.calib_mag);
//	EVENTHANDLER.trigger("sensor_update", &_args);
//
//}

SETUP_ACTION_3ARGS(avg_temp_update, 
				   const Adafruit_BMP085_Unified& bmp, 
				   const Adafruit_BNO055& bno,
				   const HIH6130& humid)
	: _bmp(bmp), _bno(bno), _humid(humid) {
	EVENTHANDLER.add_event("avg_temp_update");
}
EXECUTE_ACTION(avg_temp_update) {
	_bmp.getTemperature(&_args.BMP_Temp);
	_args.BNO_Temp = _bno.getTemp();
	_humid.readRHT();
	_args.HUM_Temp = _humid.temperature;
	_args.AVG_temp = (_args.BNO_Temp + _args.BMP_Temp + _args.HUM_Temp) / 3.0f;
	EVENTHANDLER.trigger("avg_temp_update", &_args);
}
