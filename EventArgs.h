#pragma once
#include "Arduino.h"
#include "Adafruit_BNO055.h"

class EventArgs {
public:
	virtual ~EventArgs() = 0;
};
inline EventArgs::~EventArgs() {}

struct bno_vec : EventArgs {
	bno_vec(imu::Vector<3> vec) : Vec(vec) {}
	imu::Vector<3> Vec;
};
struct bno_quat : EventArgs {
	bno_quat(imu::Quaternion quat) : Quat(quat) {}
	imu::Quaternion Quat;
};
struct Temperature : EventArgs {
	enum Units { C, F };

	Temperature() : Temp(0), TempUnits(C) {}
	explicit Temperature(int8_t temp, Units units)
		: Temp(temp), TempUnits(units) {
	}

	byte Temp;
	Units TempUnits;
};
struct Time : EventArgs {
	byte Hours = 0;
	byte Minutes = 0;
	byte Seconds = 0;
	byte Tenths = 0;
};
