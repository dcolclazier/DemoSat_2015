#pragma once
#include "Arduino.h"
#include "Adafruit_BNO055.h"

class EventArgs {
public:
	virtual ~EventArgs() = 0;
};
inline EventArgs::~EventArgs() {}

struct Time : EventArgs {
	byte Hours = 0;
	byte Minutes = 0;
	byte Seconds = 0;
	byte Tenths = 0;
};
struct bno_logger_data :EventArgs {
	imu::Vector<3> Gyro;
	imu::Vector<3> Mag;
	imu::Vector<3> Grav;
	uint8_t Temp;
	imu::Vector<3> Accel;
	imu::Vector<3> Euler;
	imu::Quaternion Quat;
	imu::Vector<3> linearAccel;
};
struct bno_temp_args : EventArgs {
	uint8_t Temp;
};
struct gravitometer_args : EventArgs {
	imu::Vector<3> Grav;
};
struct gyro_data : EventArgs {
	imu::Vector<3> Gyro;
};
struct position_args : EventArgs {
	imu::Vector<3> Euler;
	imu::Quaternion Quat;
};
struct magnetometer_args : EventArgs {
	imu::Vector<3> Mag;
};
struct accelerometer_args : EventArgs {
	imu::Vector<3> Accel;
	imu::Vector<3> linearAccel;
};
struct altitude_args :EventArgs {
	float Pressure;
	float Temp;
	float Altitude;
};
//struct bmp_alt_args :EventArgs {
//	float Pressure;
//	float Altitude;
//};

struct externalTemp_args : EventArgs {
	int8_t EXT_Temp;
};

struct temperature_args : EventArgs
{
	float BNO_Temp;
	float BMP_Temp;
	float AVG_temp;
};