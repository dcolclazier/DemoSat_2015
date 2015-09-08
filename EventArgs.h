#pragma once
#include "Arduino.h"

class EventArgs {
public:
	virtual ~EventArgs() {};
	
};

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

	explicit GravityVector(short x, short y, short z, Units units) 
		: GRV_Data_X(x), GRV_Data_Y(y), GRV_Data_Z(z), GRV_Units(units) {}

	const short GRV_Data_X;
	const short GRV_Data_Y;
	const short GRV_Data_Z;
	const Units GRV_Units;
};

struct Temperature : EventArgs {
	enum Units{ C, F };

	explicit Temperature(uint8_t temp, Units units)
		: Temp(temp), TempUnits(units) {}

	const uint8_t Temp;
	const Units TempUnits;
};

struct LinearAcceleration : EventArgs {
	enum Units { ms2, mg };
	
	explicit LinearAcceleration(short x, short y, short z, Units units) 
		: LIA_Data_X(x), LIA_Data_Y(y), LIA_Data_Z(z), LIA_Units(units) {}

	const short LIA_Data_X;
	const short LIA_Data_Y;
	const short LIA_Data_Z;
	const Units LIA_Units;
};

struct QuaternionOrientation : EventArgs {
	QuaternionOrientation(short w, short x, short y, short z) 
		: QUA_Data_w(w),QUA_Data_x(x), QUA_Data_y(y), QUA_Data_z(z) {}
	
	const short QUA_Data_w;
	const short QUA_Data_x;
	const short QUA_Data_y;
	const short QUA_Data_z;
};

struct Accelereration : EventArgs {

	Accelereration(short accel_data_x, short accel_data_y, short accel_data_z)
		: Accel_Data_X(accel_data_x),
		  Accel_Data_Y(accel_data_y),
		  Accel_Data_Z(accel_data_z) {}

	const short Accel_Data_X;
	const short Accel_Data_Y;
	const short Accel_Data_Z;
};

struct MagneticFieldStrength : EventArgs {


	MagneticFieldStrength(short mag_data_x, short mag_data_y, short mag_data_z)
		: Mag_Data_X(mag_data_x),
		  Mag_Data_Y(mag_data_y),
		  Mag_Data_Z(mag_data_z) {}

	const short Mag_Data_X;
	const short Mag_Data_Y;
	const short Mag_Data_Z;
};

struct AngularVelocity : EventArgs {

	AngularVelocity(short gyr_data_x, short gyr_data_y, short gyr_data_z)
		: Gyr_Data_X(gyr_data_x),
		  Gyr_Data_Y(gyr_data_y),
		  Gyr_Data_Z(gyr_data_z) {}

	const short Gyr_Data_X;
	const short Gyr_Data_Y;
	const short Gyr_Data_Z;
};