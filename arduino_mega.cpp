#include "arduino_mega.h"
#include "heater_actions.h"
#include "sensor_actions.h"
#include "logging_actions.h"
#include "Doorman_Actions.h"
#include "EventHandler.h"

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#include <avr/pgmspace.h>
#include <RTClib.h>


arduino_mega::arduino_mega() 
			: _logger(this), _onboardLED(LED(4)), _extTempSensor(&_OneWireBus), 
			_bnoSensor(0x28), _bmpSensor(0x55), _humidSensor(0x27), _OneWireBus(2), _lightSensor(Adafruit_SI1145()), _ledMatrix(Adafruit_BicolorMatrix()){

//INIT ALL OF THE SENSORS ON THE ARDUINO
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
	if (!_lightSensor.begin()) {
		Serial.println("Couldn't find the visible light sensor....");
		while (1);
	}
	//start humid sensor
	_humidSensor.begin();

	//start external temp sensor
	_extTempSensor.begin();
	
	//BICOLOR BACKPACK I2C assign
	_ledMatrix.begin(0x70);
	_bnoSensor.setExtCrystalUse(true);
	
	//package up sensors for logger
	SensorPackage sensor_package = SensorPackage(_logger, _realTimeClock, _onboardLED, _extTempSensor, _bnoSensor, _bmpSensor, _humidSensor, _motorShield, _OneWireBus, _lightSensor);

	//LOG DATA EVERY .1s
	EVENTHANDLER.add_eventAction(".1s", new new_sensor_update(sensor_package));
	EVENTHANDLER.add_eventAction("sensor_update", new log_all_data(_logger));
	
	//CHECK WHETHER A DOOR SHOULD BE OPENED EVERY .2S
	EVENTHANDLER.add_eventAction(".2s", new doorman_altitude_check(_bmpSensor, this));
	EVENTHANDLER.add_eventAction("sample collected", new log_door_data(_logger));
	
	//CHECK WHETHER HEATER STATUS SHOULD BE UPDATED EVERY 5s
	EVENTHANDLER.add_eventAction("5s", new avg_temp_update(_bmpSensor,_bnoSensor,_humidSensor));
	EVENTHANDLER.add_eventAction("avg_temp_update", new update_heater_status);

	//UPDATES ALTITUDE TO INITIATE MOTOR SHIELD FROM PRESET HEIGHT
	EVENTHANDLER.add_event("altitude update");
	EVENTHANDLER.add_eventAction("altitude update", new initMotorShield(_motorShield));

}

DateTime arduino_mega::getTime() const {
	return _realTimeClock.now();
}


/*
Todo:

Add in led support for calibrating the accel/gyro/fusion/magnetometer
First i wanna set up 4 leds
Turn them off to start, then when poweredm, turn to red if non calibrated
if calibration level increases, change the color of the led to yellow, then to green


*/