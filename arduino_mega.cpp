#include "arduino_mega.h"
#include "heater_actions.h"
#include "sensor_actions.h"
#include "logging_actions.h"
#include "EventHandler.h"
#include <avr/pgmspace.h>
#include <RTClib.h>
#include "external_temperature_actions.h"


arduino_mega::arduino_mega() : _logger(this), _onboardLED(LED(4)), _bnoSensor(0x28), _bmpSensor(0x55), _humidSensor(0x27){
	//start bno055 
	if (!_bnoSensor.begin()) {
		Serial.print(("9dof sensor not detected..."));
		while (1);
	}
	//start bmp180
	if (!_bmpSensor.begin()) {
		Serial.print(("bmp180 not detected..."));
		while (1);
	}
	if (!_humidSensor.begin()) {
		Serial.print(("humid sensor not detected..."));
		while (1);
	}
	delay(1000);
	_bnoSensor.setExtCrystalUse(true);

	EventHandler::instance().add_eventAction(".5s", new bno_logger_update(_bnoSensor));
	EventHandler::instance().add_eventAction("bno_logger_update", new log_bno_update(&_logger));

	//EventHandler::instance().add_eventAction("10s", new get_external_temp);
	//EventHandler::instance().add_eventAction("external_temp_update", new log_ext_temp(&_logger));


	EventHandler::instance().add_eventAction(".5s", new altitude_update(_bmpSensor));
	EventHandler::instance().add_eventAction("altitude_update", new log_altitude_update(&_logger));

	EventHandler::instance().add_eventAction("5s", new avg_temp_update(_bmpSensor, _bnoSensor));
	EventHandler::instance().add_eventAction("avg_temp_update", new update_heater_status());
}

DateTime arduino_mega::getTime() const
{
	return _realTimeClock.now();
}

/*
Todo:

Add in led support for calibrating the accel/gyro/fusion/magnetometer


*/