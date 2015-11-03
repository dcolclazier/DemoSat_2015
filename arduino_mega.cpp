#include "arduino_mega.h"
#include "heater_actions.h"
#include "sensor_actions.h"
#include "logging_actions.h"
#include "Doorman_Actions.h"
#include "EventHandler.h"
#include "Matrix_actions.h"
#include "UV_Sensor.h"

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#include <avr/pgmspace.h>
#include <RTClib.h>


arduino_mega::arduino_mega() 
			: _logger(this), _onboardLED(LED(4)), _extTempSensor(&_OneWireBus), _bnoSensor(0x28), 
			_bmpSensor(0x55), _humidSensor(0x27), _OneWireBus(A2), _visibleLightSensor(), _ledMatrix(Adafruit_BicolorMatrix()), _UVSensor(UV(A1)){
	
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
	
	_humidSensor.begin();
	_extTempSensor.begin();

	if(!_visibleLightSensor.begin()) Serial.println("Couldn't find the visible light sensor....");
	

	//BICOLOR BACKPACK I2C assign
	Serial.println("beginning LED backpack...");
	_ledMatrix.begin(0x70);
	_ledMatrix.clear();
	
	_bnoSensor.setExtCrystalUse(true);

	SensorPackage sensor_package = SensorPackage(_logger, _realTimeClock, _onboardLED, _extTempSensor, _bnoSensor, _bmpSensor, _humidSensor, _motorShield, _OneWireBus, _visibleLightSensor, _UVSensor);

	EVENTHANDLER.add_event("update_config_status");
	EVENTHANDLER.add_eventAction("update_config_status", new update_config_status(_ledMatrix));

	EVENTHANDLER.add_event("sensor_update");
	EVENTHANDLER.add_eventAction(".1s", new new_sensor_update(sensor_package, this));
	EVENTHANDLER.add_eventAction("sensor_update", new log_all_data(_logger));
	
	EVENTHANDLER.add_eventAction(".2s", new doorman_altitude_check(_bmpSensor, this));

	EVENTHANDLER.add_event("time to open");
	EVENTHANDLER.add_eventAction("time to open", new doorman_open(this));

	EVENTHANDLER.add_event("time to close");
	EVENTHANDLER.add_eventAction("time to close", new doorman_close(this));
	
	EVENTHANDLER.add_event("move door");
	EVENTHANDLER.add_eventAction("move door", new turn_motor_on(this));

	EVENTHANDLER.add_event("sample collected");
	EVENTHANDLER.add_eventAction("sample collected", new log_door_data(_logger));
		
	EVENTHANDLER.add_eventAction("5s", new avg_temp_update(_bmpSensor,_bnoSensor,_humidSensor));
	EVENTHANDLER.add_eventAction("avg_temp_update", new update_heater_status);

	EVENTHANDLER.add_eventAction("2s", new external_temp_update(_extTempSensor));
	EVENTHANDLER.add_eventAction("log_external_temp_update", new log_external_temp(_logger));
	

}

DateTime arduino_mega::getTime() const {
	return _realTimeClock.now();
}
