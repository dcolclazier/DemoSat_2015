#include "RedBoard.h"
#include "bmp_sensor_actions.h"
#include "bno_sensor_actions.h"
#include "HeaterActions.h"
#include "EventHandler.h"
#include <RTClib.h>

RedBoard::RedBoard() : _logger(this), _onboardLED(LED(3)), _bnoSensor(55){
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
	delay(1000);
	_bnoSensor.setExtCrystalUse(true);

	EVENTHANDLER.add_eventAction(".1s", new bno_full_update(_bnoSensor));
	EVENTHANDLER.add_eventAction("bno_u", new log_bno_update(&_logger));

	EVENTHANDLER.add_eventAction(".1s", new bmp_full_update(_bmpSensor));
	EVENTHANDLER.add_eventAction("bmp_u", new log_bmp_update(&_logger));

	EVENTHANDLER.add_eventAction("5s", new avg_temp_update(_bmpSensor, _bnoSensor));
	EVENTHANDLER.add_eventAction("avg_tmp", new check_temperature());
}

DateTime RedBoard::getTime() {
	return _realTimeClock.now();
}

/*
Todo:

Add in led support for calibrating the accel/gyro/fusion/magnetometer
*/