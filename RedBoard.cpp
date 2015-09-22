#include "RedBoard.h"
#include "bno_sensor_actions.h"
#include "EventHandler.h"
#include "led_flash.h"
#include <RTClib.h>


void RedBoard::SensorSetup() {
	if (!_bnoSensor.begin()) {
		Serial.print(F("9dof sensor not detected..."));
		while (1);
	}

	delay(1000);

	_bnoSensor.setExtCrystalUse(true);
	
}

RedBoard::RedBoard() : _onboardLED(13) {
	

	_realTimeClock.begin();
	//_onboardLED = LED(13); //pin 13
	_bnoSensor = 55; //I2C address 0x55
	
}

void RedBoard::InitEvents() {
	EVENTHANDLER.add_eventAction("1s", new print_time(_realTimeClock));
	EVENTHANDLER.add_eventAction(".1s", new led_flash(_onboardLED));
	EVENTHANDLER.add_eventAction(".1s", new bno_orientation_update(_bnoSensor));
	EVENTHANDLER.add_eventAction("1s", new bno_temperature_update(_bnoSensor));
	EVENTHANDLER.add_eventAction(".1s", new bno_gyro_update(_bnoSensor));
	EVENTHANDLER.add_eventAction(".1s", new bno_accel_update(_bnoSensor));
	EVENTHANDLER.add_eventAction(".1s", new bno_mag_update(_bnoSensor));
	EVENTHANDLER.add_eventAction(".1s", new bno_grav_update(_bnoSensor));
	EVENTHANDLER.add_eventAction(".1s", new bno_linearAccel_update(_bnoSensor));
}

/*
Todo:

Add in led support for calibrating the accel/gyro/fusion/magnetometer
*/