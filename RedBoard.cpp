#include "RedBoard.h"
#include "bno_sensor_actions.h"


void RedBoard::SensorSetup() {
	if (!_bnoSensor.begin()) {
		/* There was a problem detecting the BNO055 ... check your connections */
		Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
		while (1);
	}

	delay(1000);

	_bnoSensor.setExtCrystalUse(true);
}

RedBoard::RedBoard() {
	_onboardLED = 13; //pin 13
	_bnoSensor = 55; //I2C address 0x55
	SensorSetup();

	EVENTHANDLER.add_eventAction(".1s", new LEDFlash(_onboardLED));
	EVENTHANDLER.add_eventAction(".1s", new bno_orientation_update(_bnoSensor));
	EVENTHANDLER.add_eventAction(".1s", new bno_temperature_update(_bnoSensor));
	EVENTHANDLER.add_eventAction(".1s", new bno_gyro_update(_bnoSensor));
	EVENTHANDLER.add_eventAction(".1s", new bno_accel_update(_bnoSensor));
	EVENTHANDLER.add_eventAction(".1s", new bno_mag_update(_bnoSensor));
	EVENTHANDLER.add_eventAction(".1s", new bno_grav_update(_bnoSensor));
	EVENTHANDLER.add_eventAction(".1s", new bno_linearAccel_update(_bnoSensor));
}