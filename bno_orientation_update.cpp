#include "bno_orientation_update.h"

//Notice UNARYACTIONSETUP and UNARYACTIONINIT have identical signatures...
UNARYACTIONSETUP(bno_orientation_update, Adafruit_BNO055 bno) {
	_bno = bno;
	/* Initialise the sensor */
	if (!_bno.begin()) {
		/* There was a problem detecting the BNO055 ... check your connections */
		Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
		while (1);
	}

	delay(1000);

	_bno.setExtCrystalUse(true);

}


//Just need the name of the class here.. You also have access to an (args) and a (trigger)
//args contains an object with the data you need, for instance - magnetic field data (see EventArgs.h)
//(trigger) may or may not contain the object that triggered the action
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

