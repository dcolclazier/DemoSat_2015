#pragma once
#include "Arduino.h"
#include "Adafruit_BNO055.h"
#include <RTClib.h>
#include <OneWire.h>
#include <Adafruit_MotorShield.h>
#include <HIH6130.h>
#include <DallasTemperature.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_SI1145.h>
#include "LED.h"
#include "sd_shield.h"
#include "UV_Sensor.h"

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

struct AltitudeData : EventData {
	float current_alt_in_meters;
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
	bool hasntbeenopenedbefore = true;
};
struct config_data : EventData
{
	uint8_t calib_system, calib_gyro, calib_accel, calib_mag = 0;
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
	float UV_Sensor;
	uint8_t calib_fusion, calib_gyro, calib_accel, calib_mag = 0;
};

struct SensorPackage : EventData
{
	SensorPackage(const SD_Shield& logger, const RTC_DS1307& clock, const LED& led, const DallasTemperature& ext_temp,
		const Adafruit_BNO055& bno, const Adafruit_BMP085_Unified& bmp, const HIH6130& humid, 
		const Adafruit_MotorShield afms, const OneWire& oneWire, const Adafruit_SI1145 visible , const UV& UltraViolet) :
		_logger(logger), _realTimeClock(clock), _onboardLED(led), _humidSensor(humid), _afms(afms),
		_OneWireBus(oneWire), _visibleLight(visible), _extTemp(ext_temp), _uvLight(UltraViolet)
	{
		
	}
	SD_Shield _logger;
	RTC_DS1307 _realTimeClock;
	LED _onboardLED;
	DallasTemperature _extTemp;
	Adafruit_BNO055 _bno;
	Adafruit_BMP085_Unified _bmp;
	HIH6130 _humidSensor;
	Adafruit_MotorShield _afms;
	//Sparkfun_Humid _humidSensor;
	OneWire _OneWireBus;
	Adafruit_SI1145 _visibleLight;
	UV _uvLight;

};
struct new_sensor_data : EventData
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
	uint16_t IR;
	uint16_t visible;
	uint16_t UltraViolet;
	float UltraVioletVoltage;

};

struct temperature_data : EventData
{
	float BNO_Temp;
	float BMP_Temp;
	float HUM_Temp;
	float AVG_temp;
};