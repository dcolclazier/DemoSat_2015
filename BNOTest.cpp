#include "BNOTest.h"


//Notice UNARYACTIONSETUP and UNARYACTIONINIT have identical signatures...
UNARYACTIONSETUP(BNOTest, Adafruit_BNO055 bno) {
	_bno = bno;
	Serial.println("Orientation Sensor Test"); Serial.println("");

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
ACTIONEXECUTE(BNOTest) {

	sensors_event_t event;
	_bno.getEvent(&event);

	///* Display the floating point data */
	Serial.print("X: ");
	Serial.print(event.orientation.x, 4);
	Serial.print("\tY: ");
	Serial.print(event.orientation.y, 4);
	Serial.print("\tZ: ");
	Serial.print(event.orientation.z, 4);
	Serial.println("");
}

