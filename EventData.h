#pragma once
#include "Arduino.h"
#include "Adafruit_BNO055.h"
#include <RTClib.h>

class turn_motor_off;
class EventData {
public:
	virtual ~EventData() = 0;
};
inline EventData::~EventData() {}

struct Time : EventData {
	byte Hours = 0;
	byte Minutes = 0;
	byte Seconds = 0;
	byte Tenths = 0;
};

struct Door_Data : EventData{
	//Door_Data(int door_num) : door_number(door_num) {}
	Door_Data(int door_num, unsigned long open_time, unsigned long close_time) : door_number(door_num), openTime(open_time), closeTime(close_time) {}
	DateTime door_open_start;
	DateTime door_open_finish;
	DateTime door_close_start;
	DateTime door_close_finish;

	int door_number = 0;
	int direction = 0;
	bool moving = false;
	unsigned long door_start_millis = 0;
	turn_motor_off* motor_action = 0;
	unsigned long openTime = 3750;
	unsigned long closeTime = 3750;
	bool closed = true;
};

struct sensor_data : EventData
{
	imu::Vector<3> Gyro;
	imu::Vector<3> Mag;
	imu::Vector<3> Grav;
	float bno_Temp;
	imu::Vector<3> Accel;
	imu::Vector<3> Euler;
	imu::Quaternion Quat;
	imu::Vector<3> linearAccel;
	float ext_Temp;
	float Pressure;
	float bmp_Temp;
	float Altitude;
	float Rel_Humidity;
	float Humid_Temp;
	uint8_t calib_fusion, calib_gyro, calib_accel, calib_mag = 0;
};

struct temperature_data : EventData
{
	float BNO_Temp;
	float BMP_Temp;
	float HUM_Temp;
	float AVG_temp;
};