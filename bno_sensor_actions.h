#pragma once
#include "EventAction.h"
#include "EventArgs.h"
#include "Adafruit_BNO055.h"

ACTION(bno_gyro_update) {
	UNARYACTIONINIT(bno_gyro_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	GyroData _gyro;
};

ACTION(bno_mag_update) {
	UNARYACTIONINIT(bno_mag_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	MagneticFieldStrength _mag;
};

ACTION(bno_grav_update) {
	UNARYACTIONINIT(bno_grav_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	GravityVector _grav;
};

ACTION(bno_temperature_update) {
	UNARYACTIONINIT(bno_temperature_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	Temperature _temp;
};

ACTION(bno_accel_update) {
	UNARYACTIONINIT(bno_accel_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	AccelVector _acceleration;
};

ACTION(bno_orientation_update) {
	UNARYACTIONINIT(bno_orientation_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
};

ACTION(bno_linearAccel_update) {
	UNARYACTIONINIT(bno_linearAccel_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	LinearAcceleration _linear;
};