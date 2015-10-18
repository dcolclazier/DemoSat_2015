#include "arduino_mega.h"
#include "heater_actions.h"
#include "sensor_actions.h"
#include "logging_actions.h"
#include "EventHandler.h"
#include <avr/pgmspace.h>
#include <RTClib.h>
#include "external_temperature_actions.h"

//CREATE_ACTION(some_name)
	//put variables here you want the action to remember for the whole flight.
//END_CREATE
//
//SETUP_ACTION(some_name) {
//	//this runs once, when the action is created
//}
//
//EXECUTE_ACTION(some_name) {
//	//this runs every trigger.
//}
//
//void test() {
//	EVENTHANDLER.add_event("hooba");
//	EVENTHANDLER.add_eventAction("hooba", new some_name);
//}
//
//void somewhereElse() {
//	EVENTHANDLER.trigger("hooba");
//}

arduino_mega::arduino_mega() : _logger(this), _onboardLED(LED(4)), _bnoSensor(0x28), _bmpSensor(0x55), _humidSensor(0x27){
	//start bno055 
	if (!_bnoSensor.begin()) {
		Serial.print(F("9dof sensor not detected..."));
		while (1);
	}
	//start bmp180
	if (!_bmpSensor.begin()) {
		Serial.print(F("bmp180 not detected..."));
		while (1);
	}
	if (!_humidSensor.begin()) {
		Serial.print(F("humid sensor not detected..."));
		while (1);
	}
	delay(1000);
	_bnoSensor.setExtCrystalUse(true);

	EVENTHANDLER.add_eventAction(".5s", new bno_logger_update(_bnoSensor));
	EVENTHANDLER.add_eventAction("bno_logger_update", new log_bno_update(&_logger));

	EVENTHANDLER.add_eventAction("10s", new get_external_temp);
	EVENTHANDLER.add_eventAction("external_temp_update", new log_ext_temp(&_logger));


	EVENTHANDLER.add_eventAction(".5s", new altitude_update(_bmpSensor));
	EVENTHANDLER.add_eventAction("altitude_update", new log_altitude_update(&_logger));
	EVENTHANDLER.add_eventAction("altitude_update", new doorman_check);

	EVENTHANDLER.add_eventAction("5s", new avg_temp_update(_bmpSensor, _bnoSensor));
	EVENTHANDLER.add_eventAction("avg_temp_update", new update_heater_status());
}

DateTime arduino_mega::getTime() {
	return _realTimeClock.now();
}

/*
Todo:

Add in led support for calibrating the accel/gyro/fusion/magnetometer


*/