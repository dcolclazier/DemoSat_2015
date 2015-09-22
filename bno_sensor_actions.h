#pragma once
#include "EventHandler.h"
#include "Adafruit_BNO055.h"

ACTION(bno_gyro_update) {
	UNARYACTIONINIT(bno_gyro_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	bno_vec _args;
};

ACTION(bno_mag_update) {
	UNARYACTIONINIT(bno_mag_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	bno_vec _args;
	
};

ACTION(bno_grav_update) {
	UNARYACTIONINIT(bno_grav_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	bno_vec _args;
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
	bno_vec _args;
};

ACTION(bno_orientation_update) {
	UNARYACTIONINIT(bno_orientation_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	bno_quat _quat;
};

ACTION(bno_linearAccel_update) {
	UNARYACTIONINIT(bno_linearAccel_update, Adafruit_BNO055 bno);

private:
	Adafruit_BNO055 _bno;
	bno_vec _args;
};