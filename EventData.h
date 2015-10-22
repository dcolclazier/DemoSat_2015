#pragma once
#include "Arduino.h"
#include "Adafruit_BNO055.h"
#include <RTClib.h>

class motor_on;
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

struct DoorOpen_Data : EventData
{
	DoorOpen_Data() : door_number(0), door_start_millis(0), motor_action(NULL) {}
	DateTime door_open_start;
	DateTime door_open_finish;
	DateTime door_close_start;
	DateTime door_close_finish;
	int door_number;
	unsigned long door_start_millis;
	motor_on* motor_action;
};

struct Door_Data : EventData{
	Door_Data(int door_num) : door_number(door_num) {}
	DateTime door_open_start;
	DateTime door_open_finish;
	DateTime door_close_start;
	DateTime door_close_finish;
	int door_number;
	int direction;
	bool moving;
	unsigned long door_start_millis;
	motor_on* motor_action;

};

struct DoorClose_Data : EventData
{
	DateTime door_close_start;
	DateTime door_close_finish;
	int door_number;
};

struct DOOR_DATA : EventData
{
	int door_to_open = 0;
	int door_to_close = 0;
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
};
//struct bno_temp_args : EventData {
//	uint8_t Temp;
//};
//struct gravitometer_args : EventData {
//	imu::Vector<3> Grav;
//};
//struct gyro_data : EventData {
//	imu::Vector<3> Gyro;
//};
//struct position_args : EventData {
//	imu::Vector<3> Euler;
//	imu::Quaternion Quat;
//};
//struct magnetometer_args : EventData {
//	imu::Vector<3> Mag;
//};
//struct accelerometer_args : EventData {
//	imu::Vector<3> Accel;
//	imu::Vector<3> linearAccel;
//};
//struct altitude_args :EventData {
//	float Pressure;
//	float Temp;
//	float Altitude;
//};
//struct bmp_alt_args :EventData {
//	float Pressure;
//	float Altitude;
//};

//struct externalTemp_args : EventData {
//	int8_t EXT_Temp;
//};

struct temperature_data : EventData
{
	float BNO_Temp;
	float BMP_Temp;
	float HUM_Temp;
	float AVG_temp;
};