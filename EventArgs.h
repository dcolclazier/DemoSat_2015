#pragma once
#include "Arduino.h"
#include "Adafruit_BNO055.h"

class EventArgs {
public:
	virtual ~EventArgs() = 0;
};
inline EventArgs::~EventArgs() {}

//struct bno_args : EventArgs {
//	bno_args() {}
//	explicit bno_args(imu::Vector<3> vec) : Vec(vec) {}
//	imu::Vector<3> Vec;
//};
//
//struct bno_quat : EventArgs {
//	bno_quat(){}
//	explicit bno_quat(imu::Quaternion quat) : Quat(quat) {}
//	imu::Quaternion Quat;
//};
//struct Temperature : EventArgs {
//	enum Units { C, F };
//
//	Temperature() : Temp(0), TempUnits(C) {}
//	explicit Temperature(int8_t temp, Units units)
//		: Temp(temp), TempUnits(units) {
//	}
//
//	byte Temp;
//	Units TempUnits;
//};
struct Time : EventArgs {
	byte Hours = 0;
	byte Minutes = 0;
	byte Seconds = 0;
	byte Tenths = 0;
};
struct bno_full_args :EventArgs {
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
struct bno_grav_args : EventArgs {
	imu::Vector<3> Grav;
};
struct bno_gyro_args : EventArgs {
	imu::Vector<3> Gyro;
};
struct bno_position_args : EventArgs {
	imu::Vector<3> Euler;
	imu::Quaternion Quat;
};
struct bno_mag_args : EventArgs {
	imu::Vector<3> Mag;
};
struct bno_accel_args : EventArgs {
	imu::Vector<3> Accel;
	imu::Vector<3> linearAccel;
};
struct bmp_full_args :EventArgs {
	float Pressure;
	float Temp;
	float Altitude;
};
struct bmp_alt_args :EventArgs {
	float Pressure;
	float Altitude;
};

struct avg_temp_args : EventArgs
{
	float BNO_Temp;
	float BMP_Temp;
	float AVG_Temp;
};