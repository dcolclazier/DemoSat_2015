#include "bno_sensor_actions.h"
#include "EventArgs.h"
#include "EventAction.h"
#include "EventHandler.h"
#include "Event.h"

UNARYACTIONSETUP(bno_gyro_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("bno_gyr_upd", new Event);
}
ACTIONEXECUTE(bno_gyro_update) {

	imu::Vector<3> vec = _bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
	_gyro.Gyro_Data_X = vec.x();
	_gyro.Gyro_Data_Y = vec.y();
	_gyro.Gyro_Data_Z = vec.z();
	EVENTHANDLER.trigger("bno_gyr_upd", &_gyro, &_bno);
}

UNARYACTIONSETUP(bno_mag_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("bno_mag_upd", new Event);
}
ACTIONEXECUTE(bno_mag_update) {

	imu::Vector<3> vec = _bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
	_mag.Mag_Data_X = vec.x();
	_mag.Mag_Data_Y = vec.y();
	_mag.Mag_Data_Z = vec.z();
	EVENTHANDLER.trigger("bno_mag_upd", &_mag, &_bno);
}

UNARYACTIONSETUP(bno_grav_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("bno_grav_upd", new Event);
}
ACTIONEXECUTE(bno_grav_update) {

	imu::Vector<3> vec = _bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
	_grav.GRV_Data_X = vec.x();
	_grav.GRV_Data_Y = vec.y();
	_grav.GRV_Data_Z = vec.z();
	EVENTHANDLER.trigger("bno_grav_upd", &_grav, &_bno);
}

UNARYACTIONSETUP(bno_temperature_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("bno_tmp_upd", new Event);
}
ACTIONEXECUTE(bno_temperature_update) {

	_temp.Temp = _bno.getTemp();
	EVENTHANDLER.trigger("bno_tmp_upd", &_temp, &_bno);
}

UNARYACTIONSETUP(bno_accel_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("bno_accel_upd", new Event);
}
ACTIONEXECUTE(bno_accel_update) {

	imu::Vector<3> vec = _bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
	_acceleration.Accel_Data_X = vec.x();
	_acceleration.Accel_Data_Y = vec.y();
	_acceleration.Accel_Data_Z = vec.z();
	EVENTHANDLER.trigger("bno_accel_upd", &_acceleration, &_bno);
}

UNARYACTIONSETUP(bno_orientation_update, Adafruit_BNO055 bno) {
	_bno = bno;
}
ACTIONEXECUTE(bno_orientation_update) {

	imu::Quaternion quaternion = _bno.getQuat();

	Serial.flush();
	Serial.print(quaternion.y(), 4);
	Serial.print(",");
	Serial.print(quaternion.z(), 4);
	Serial.print(",");
	Serial.print(quaternion.x(), 4);
	Serial.print(",");
	Serial.print(quaternion.w(), 4);
	Serial.println();
}

UNARYACTIONSETUP(bno_linearAccel_update, Adafruit_BNO055 bno) {
	_bno = bno;
}
ACTIONEXECUTE(bno_linearAccel_update) {

	imu::Vector<3> vec = _bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
	_linear.LIA_Data_X = vec.x();
	_linear.LIA_Data_Y = vec.y();
	_linear.LIA_Data_Z = vec.z();
	EVENTHANDLER.trigger("bno_linear_upd", &_linear, &_bno);

	
}

