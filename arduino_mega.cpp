#include "arduino_mega.h"
#include "heater_actions.h"
#include "sensor_actions.h"
#include "logging_actions.h"
#include "Doorman_Actions.h"
#include "CameraActions.h"
#include "EventHandler.h"
#include "Matrix_actions.h"
#include "UV_Sensor.h"

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#include <avr/pgmspace.h>
#include <RTClib.h>


arduino_mega::arduino_mega() 
			: _logger(this), _onboardLED(LED(4)), _extTempSensor(&_OneWireBus), _UVSensor(UV(A1)), 
			_bnoSensor(0x28), _bmpSensor(0x55), _humidSensor(0x27), _OneWireBus(2), _lightSensor(), _ledMatrix(Adafruit_BicolorMatrix()){
	
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
	//start humid sensor
	_humidSensor.begin();

	//start external temp sensor
	_extTempSensor.begin();
	
	_lightSensor = Adafruit_SI1145();

	//_UVSensor = UltraViolet(A1);

	if(!_lightSensor.begin())
	{
		Serial.println("Couldn't find the visible light sensor....");
	}

	//BICOLOR BACKPACK I2C assign
	Serial.println("beginning LED backpack...");
	_ledMatrix.begin(0x70);
	_ledMatrix.clear();



	EVENTHANDLER.add_event("update_config_status");
	EVENTHANDLER.add_event("altitude update");
	SensorPackage sensor_package = SensorPackage(_logger, _realTimeClock, _onboardLED, _extTempSensor, _bnoSensor, _bmpSensor, _humidSensor, _motorShield, _OneWireBus, _lightSensor, _UVSensor);

	_bnoSensor.setExtCrystalUse(true);

	EVENTHANDLER.add_eventAction("update_config_status", new update_config_status(_ledMatrix));
	
	EVENTHANDLER.add_eventAction(".1s", new new_sensor_update(sensor_package));
	EVENTHANDLER.add_eventAction("sensor_update", new log_all_data(_logger));
	
	EVENTHANDLER.add_eventAction(".2s", new doorman_altitude_check(_bmpSensor, this));
	EVENTHANDLER.add_eventAction("door moved", new log_door_data(_logger));
		
	EVENTHANDLER.add_eventAction("5s", new avg_temp_update(_bmpSensor,_bnoSensor,_humidSensor));
	EVENTHANDLER.add_eventAction("avg_temp_update", new update_heater_status);

	EVENTHANDLER.add_eventAction("take a picture", new take_picture);


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