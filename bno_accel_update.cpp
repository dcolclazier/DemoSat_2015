#include "bno_accel_update.h"
#include "EventArgs.h"
#include "EventAction.h"
#include "EventHandler.h"
#include "Event.h"

UNARYACTIONSETUP(bno_accel_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("bno_gyr_upd", new Event);
}
ACTIONEXECUTE(bno_accel_update) {

	imu::Vector<3> vec = _bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
	/*_acceleration.Accel_Data_X = vec.x();
	_acceleration.Accel_Data_Y = vec.y();
	_acceleration.Accel_Data_Z = vec.z();
	EVENTHANDLER.trigger("bno_gyr_upd", &_acceleration, &_bno);*/
}