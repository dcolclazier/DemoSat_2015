#pragma once
#include "EventHandler.h"
#include "Adafruit_BNO055.h"
#include "Adafruit_BMP085_U.h"

//BNO055 GYROSCOPE UPDATE - to trigger, use event name "bn_gy_u"
//args should be casted into a bno_gyro_args
//args contains gyroscope data
ACTION(bno_gyro_update) {
	UNARYACTIONINIT(bno_gyro_update, bno_gyro_args, Adafruit_BNO055 bno);

	Adafruit_BNO055 _bno;
};

//BNO055 MAGNETOMETER UPDATE - to trigger, use event name "bn_m_u"
//args should be casted into a bno_mag_args
//args contain magnetometer data
ACTION(bno_mag_update) {
	UNARYACTIONINIT(bno_mag_update, bno_mag_args, Adafruit_BNO055 bno);

	Adafruit_BNO055 _bno;
};

//BNO055 GRAVITOMETER UPDATE - to trigger, use event name "bn_gr_u"
//args should be casted into a bno_grav_args
//args contain gravitometer data
ACTION(bno_grav_update) {
	UNARYACTIONINIT(bno_grav_update, bno_grav_args, Adafruit_BNO055 bno);
	Adafruit_BNO055 _bno;
};

//BNO055 ACCELERATION UPDATE - to trigger, use event name "bn_a_u"
//args should be casted into a bno_accel_args
//args contain accelerometer and linear acceleration
ACTION(bno_accel_update) {
	UNARYACTIONINIT(bno_accel_update, bno_accel_args, Adafruit_BNO055 bno);
	Adafruit_BNO055 _bno;
};

//BNO055 POSITION UPDATE - to trigger, use event name "bn_p_u"
//args should be casted into a bno_position_args
//args contains both euler heading and quaternion
ACTION(bno_position_update) {
	UNARYACTIONINIT(bno_position_update, bno_position_args, Adafruit_BNO055 bno);
	Adafruit_BNO055 _bno;
};

//BNO055 Full UPDATE - to trigger, use event name "bn_full_u"
//args should be casted into a bno_full_args
//args contains all possible data from bno_055 sensor 
//use this for logging data - it's memory intensive.
ACTION(bno_full_update) {
	UNARYACTIONINIT(bno_full_update, bno_full_args, Adafruit_BNO055 bno);
	Adafruit_BNO055 _bno;
};

//BMP SENSOR UPDATE - to trigger, use event name "alt_u"
//args should be casted into a bmp_full_args
//args contains temperature, pressure and altitude
ACTION(altitude_sensor_update)
{
	UNARYACTIONINIT(altitude_sensor_update, bmp_full_args, Adafruit_BMP085_Unified bmp);

	Adafruit_BMP085_Unified _bmp;
	const float _seaLevelPressure = 1012.8f;
};

//AVG TEMP UPDATE - to trigger, use event name "avg_tmp"
//args should be casted into a avg_temp_args
//args contains temperature, pressure and altitude
ACTION(avg_temp_update){
	BINARYACTIONINIT(avg_temp_update, avg_temp_args, Adafruit_BMP085_Unified bmp, Adafruit_BNO055 bno);
	
	Adafruit_BMP085_Unified _bmp;
	Adafruit_BNO055 _bno;
};