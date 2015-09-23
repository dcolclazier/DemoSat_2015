#include "bno_sensor_actions.h"
#include "EventHandler.h"

//UNARYACTIONSETUP(bno_gyro_update, Adafruit_BNO055 bno) : _args(0) {
//	_bno = bno;
//	EVENTHANDLER.add_event("gy_u", new Event);
//}
//ACTIONEXECUTE(bno_gyro_update) {
//
//	_args.Vec = _bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
//	EVENTHANDLER.trigger("gy_u", &_args, &_bno);
//}
//
//UNARYACTIONSETUP(bno_mag_update, Adafruit_BNO055 bno) : _args(0) {
//	_bno = bno;
//	EVENTHANDLER.add_event("ma_u", new Event);
//}
//ACTIONEXECUTE(bno_mag_update) {
//
//	_args.Vec = _bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
//	EVENTHANDLER.trigger("ma_u", &_args, &_bno);
//}
//
//UNARYACTIONSETUP(bno_grav_update, Adafruit_BNO055 bno) : _args(0) {
//	_bno = bno;
//	EVENTHANDLER.add_event("gr_u", new Event);
//}
//ACTIONEXECUTE(bno_grav_update) {
//
//	_args.Vec = _bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
//	EVENTHANDLER.trigger("gr_u", &_args, &_bno);
//}
//
//UNARYACTIONSETUP(bno_temperature_update, Adafruit_BNO055 bno) {
//	_bno = bno;
//	EVENTHANDLER.add_event("t_u", new Event);
//}
//ACTIONEXECUTE(bno_temperature_update) {
//
//	_temp.Temp = _bno.getTemp();
//	EVENTHANDLER.trigger("t_u", &_temp, &_bno);
//}
//
//UNARYACTIONSETUP(bno_accel_update, Adafruit_BNO055 bno) : _args(0) {
//	_bno = bno;
//	EVENTHANDLER.add_event("ac_u", new Event);
//}
//ACTIONEXECUTE(bno_accel_update) {
//
//	_args.Vec = _bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
//	EVENTHANDLER.trigger("eu_u", &_args, &_bno);
//}
//UNARYACTIONSETUP(bno_euler_update, Adafruit_BNO055 bno) : _args(0) {
//	_bno = bno;
//	EVENTHANDLER.add_event("eu_u", new Event);
//}
//ACTIONEXECUTE(bno_euler_update) {
//
//	_args.Vec = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
//	EVENTHANDLER.trigger("ac_u", &_args, &_bno);
//}
//
//UNARYACTIONSETUP(bno_orientation_update, Adafruit_BNO055 bno) : _quat(imu::Quaternion()){
//	_bno = bno;
//	EVENTHANDLER.add_event("or_u", new Event);
//}
//ACTIONEXECUTE(bno_orientation_update) {
//
//	_quat.Quat = _bno.getQuat();
//	EVENTHANDLER.trigger("or_u", &_quat, &_bno);
//}
//
//UNARYACTIONSETUP(bno_linearAccel_update, Adafruit_BNO055 bno) : _args(0) {
//	_bno = bno;
//	EVENTHANDLER.add_event("li_u", new Event);
//}
//ACTIONEXECUTE(bno_linearAccel_update) {
//
//	_args.Vec = _bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
//	EVENTHANDLER.trigger("li_u", &_args, &_bno);
//}
UNARYACTIONSETUP(bno_full_update, Adafruit_BNO055 bno)  {
	_bno = bno;
	EVENTHANDLER.add_event("bno_u", new Event);
}
ACTIONEXECUTE(bno_full_update) {

	_args.Gyro = _bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
	_args.Mag = _bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
	_args.Grav = _bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
	_args.Temp = _bno.getTemp();
	_args.Accel = _bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
	_args.Euler = _bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	_args.Quat = _bno.getQuat();
	_args.linearAccell = _bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
	EVENTHANDLER.trigger("bno_u", &_args, &_bno);
}

