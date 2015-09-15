#include "bno_gyro_update.h"
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