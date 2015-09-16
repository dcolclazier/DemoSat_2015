#pragma once
#include "Arduino.h"

class EventArgs {
public:
	virtual ~EventArgs() = 0;
	
};
inline EventArgs::~EventArgs() {}


struct Orientation : EventArgs {
	enum Units { rad, deg };

	Orientation(short eul_heading, short eul_roll, short eul_pitch, Units eul_units)
		: EUL_Heading(eul_heading), EUL_Roll(eul_roll), EUL_Pitch(eul_pitch), EUL_Units(eul_units) {}
	
	const short EUL_Heading;
	const short EUL_Roll;
	const short EUL_Pitch;
	const Units EUL_Units;
};

struct GravityVector : EventArgs {
	enum Units { ms2, mg };

	GravityVector() : GRV_Data_X(0) , GRV_Data_Y(0), GRV_Data_Z(0), GRV_Units(ms2) {}
	explicit GravityVector(short x, short y, short z, Units units) 
		: GRV_Data_X(x), GRV_Data_Y(y), GRV_Data_Z(z), GRV_Units(units) {}

	short GRV_Data_X;
	short GRV_Data_Y;
	short GRV_Data_Z;
	Units GRV_Units;
};

struct Temperature : EventArgs {
	enum Units{ C, F };

	Temperature() : Temp(0), TempUnits(C) {}
	explicit Temperature(int8_t temp, Units units)
		: Temp(temp), TempUnits(units) {}

	int8_t Temp;
	Units TempUnits;
};

struct LinearAcceleration : EventArgs {
	enum Units { ms2, mg };
	
	LinearAcceleration() : LIA_Data_X(0), LIA_Data_Y(0), LIA_Data_Z(0), LIA_Units(ms2) {}
	explicit LinearAcceleration(short x, short y, short z, Units units) 
		: LIA_Data_X(x), LIA_Data_Y(y), LIA_Data_Z(z), LIA_Units(units) {}

	short LIA_Data_X;
	short LIA_Data_Y;
	short LIA_Data_Z;
	Units LIA_Units;
};

struct QuaternionOrientation : EventArgs {
	QuaternionOrientation(short w, short x, short y, short z) 
		: QUA_Data_w(w),QUA_Data_x(x), QUA_Data_y(y), QUA_Data_z(z) {}
	
	const short QUA_Data_w;
	const short QUA_Data_x;
	const short QUA_Data_y;
	const short QUA_Data_z;
};

struct AccelVector : EventArgs {

	AccelVector():Accel_Data_X(0), Accel_Data_Y(0), Accel_Data_Z(0) {}
	AccelVector(short accel_data_x, short accel_data_y, short accel_data_z)
		: Accel_Data_X(accel_data_x),
		  Accel_Data_Y(accel_data_y),
		  Accel_Data_Z(accel_data_z) {}

	short Accel_Data_X;
	short Accel_Data_Y;
	short Accel_Data_Z;
};

struct Time : EventArgs {
	int Hours = 0;
	int Minutes = 0;
	int Seconds = 0;
	int Tenths = 0;
};

struct MagneticFieldStrength : EventArgs {

	MagneticFieldStrength() : Mag_Data_X(0), Mag_Data_Y(0), Mag_Data_Z(0) {}
	MagneticFieldStrength(short mag_data_x, short mag_data_y, short mag_data_z)
		: Mag_Data_X(mag_data_x),
		  Mag_Data_Y(mag_data_y),
		  Mag_Data_Z(mag_data_z) {}

	short Mag_Data_X;
	short Mag_Data_Y;
	short Mag_Data_Z;
};

struct GyroData : EventArgs {

	GyroData() : Gyro_Data_X(0), Gyro_Data_Y(0), Gyro_Data_Z(0) {}
	GyroData(short gyr_data_x, short gyr_data_y, short gyr_data_z)
		: Gyro_Data_X(gyr_data_x),
		  Gyro_Data_Y(gyr_data_y),
		  Gyro_Data_Z(gyr_data_z) {}

	short Gyro_Data_X;
	short Gyro_Data_Y;
	short Gyro_Data_Z;
};