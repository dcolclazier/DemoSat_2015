#include "RedBoard.h"
#include "bno_orientation_update.h"
#include "bno_temperature_update.h"
#include "bno_gyro_update.h"
#include "bno_accel_update.h"

RedBoard::RedBoard() {
	_onboardLED = 13; //pin 13
	_bnoSensor = 55; //I2C address 0x55

	EVENTHANDLER.add_eventAction(".1s", new LEDFlash(_onboardLED));
	EVENTHANDLER.add_eventAction(".1s", new bno_orientation_update(_bnoSensor));
	//EVENTHANDLER.add_eventAction("1s", new bno_temperature_update(_bnoSensor));
	//EVENTHANDLER.add_eventAction("5s", new bno_gyro_update(_bnoSensor));
	//EVENTHANDLER.add_eventAction("1s", new bno_accel_update(_bnoSensor));
}