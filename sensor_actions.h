#pragma once
#include "EventHandler.h"
#include "Adafruit_BNO055.h"
#include "Adafruit_BMP085_U.h"
#include "HIH6130.h"
#include "DallasTemperature.h"

//Here are some newer actions still - they're called
// trigger actions. They work the same as the other actions,

/* with one big difference - they are responsible for triggering
 an event themselves. For instance - these actions respond to certain time intervals, grab data from the sensors, and then send that data in a new event trigger. 
 
 The thing you have to have for this is the correct 'type' of 
 data package. When we update the gyroscope, we fill up and send
 the gyro_data data package - it holds gyroscode data*/


//BNO055 GYROSCOPE UPDATE 
CREATE_EVENT_TRIGGERING_ACTION_1ARG(gyro_update, gyro_data, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
END_CREATE

//BNO055 MAGNETOMETER UPDATE 
CREATE_EVENT_TRIGGERING_ACTION_1ARG(magnetometer_update, magnetometer_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
END_CREATE

//BNO055 GRAVITOMETER UPDATE - to trigger, use event name "gravitometer_update"
//args contain gravitometer data
CREATE_EVENT_TRIGGERING_ACTION_1ARG(gravitometer_update, gravitometer_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
END_CREATE

CREATE_EVENT_TRIGGERING_ACTION_4ARGS(sensor_update, sensor_data, Adafruit_BNO055 bno, Adafruit_BMP085_Unified bmp, DallasTemperature sensor, HIH6130 humid_sensor)

Adafruit_BNO055 _bno;
Adafruit_BMP085_Unified _bmp;
DallasTemperature _extTemp;
HIH6130 _humidSensor;
float _seaLevelPressure = 1012.8f;

END_CREATE




CREATE_EVENT_TRIGGERING_ACTION(get_external_temp, externalTemp_args)

OneWire oneWireBus;
DallasTemperature sensors;

END_CREATE

//BNO055 ACCELERATION UPDATE - to trigger, use event name "accelerometer_update"
//args contain accelerometer and linear acceleration
CREATE_EVENT_TRIGGERING_ACTION_1ARG(accelerometer_update, accelerometer_args, Adafruit_BNO055 bno);
	Adafruit_BNO055 _bno;
END_CREATE

//BNO055 POSITION UPDATE 
CREATE_EVENT_TRIGGERING_ACTION_1ARG(position_update, position_args, Adafruit_BNO055 bno);
	Adafruit_BNO055 _bno;
END_CREATE

//BNO055 Full UPDATE - to trigger, use event name "bno_logger_update"
//args contains all possible data from bno_055 sensors 
//use this for logging data - it's memory intensive.
CREATE_EVENT_TRIGGERING_ACTION_1ARG(bno_logger_update, bno_logger_data, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
END_CREATE

//BMP SENSOR UPDATE - to trigger, use event name "altitude_update"
//args contains temperature, pressure and altitude
CREATE_EVENT_TRIGGERING_ACTION_1ARG(altitude_update, altitude_args, Adafruit_BMP085_Unified bmp)

	Adafruit_BMP085_Unified _bmp;
	const float _seaLevelPressure = 1012.8f;
END_CREATE

//AVG TEMP UPDATE - to trigger, use event name "avg_tmp"
//args contains temperature, pressure and altitude
CREATE_EVENT_TRIGGERING_ACTION_2ARGS(avg_temp_update, temperature_args, Adafruit_BMP085_Unified bmp, Adafruit_BNO055 bno)
	
	Adafruit_BMP085_Unified _bmp;
	Adafruit_BNO055 _bno;
END_CREATE