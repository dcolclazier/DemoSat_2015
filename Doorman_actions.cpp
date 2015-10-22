#include "Doorman_Actions.h"
#include <Adafruit_MotorShield.h>
#include "EventHandler.h"
#include "arduino_mega.h"
SETUP_ACTION_2ARGS(doorman_altitude_check, Adafruit_BMP085_Unified bmp, arduino_mega* arduino)
{
	_bmp = bmp;
	_arduino = arduino;
	EVENTHANDLER.add_event("open door");
	EVENTHANDLER.add_event("close door");
}

EXECUTE_ACTION(doorman_altitude_check) {
	sensors_event_t event;
	float temp;
	_bmp.getEvent(&event);
	_bmp.getTemperature(&temp);
	float altitude = _bmp.pressureToAltitude(1012.8f, event.pressure, temp);


	if (altitude == 1000) {
		_args.door_to_open = 1;
		EVENTHANDLER.trigger("open door", &_args, &_arduino);
	}
	if (altitude == 5000) {
		_args.door_to_open = 2;
		_args.door_to_close = 1;
		EVENTHANDLER.trigger("open door", &_args, &_arduino);
		EVENTHANDLER.trigger("close door", &_args, &_arduino);
	}
	if (altitude == 10000) {
		_args.door_to_open = 3;
		_args.door_to_close = 2;
		EVENTHANDLER.trigger("open door", &_args, &_arduino);
		EVENTHANDLER.trigger("close door", &_args, &_arduino);
	}
	if (altitude == 10000) {
		_args.door_to_open = 4;
		_args.door_to_close = 3;
		EVENTHANDLER.trigger("open door", &_args, &_arduino);
		EVENTHANDLER.trigger("close door", &_args, &_arduino);
	}


}
SETUP_ACTION(doorman_open)
{
	EVENTHANDLER.add_event("Door opened");
}

EXECUTE_ACTION(doorman_open)
{
	DOOR_DATA* data = static_cast<DOOR_DATA*>(args);
	arduino_mega* arduino = static_cast<arduino_mega*>(trigger);

	_args.door_number = data->door_to_open;
	_args.door_open_start = arduino->getTime();

	//turn on the motor for the door we're opening.
	data->door_to_open;
		
	_args.motor_action = new motor_on(_args, arduino);
	EVENTHANDLER.add_eventAction(".1s", _args.motor_action);

}
SETUP_ACTION_2ARGS(motor_on, const DoorOpen_Data& data, const arduino_mega* arduino) :_data(data), _arduino(arduino) {}
EXECUTE_ACTION(motor_on) {
	//if we shouldn't turn off the motor, don't.
	if (millis() - _data.door_start_millis < motor_run_time) return;
	if (off) return;

	//turn off motor and remove this motor_on action from the eventhandler.
	//NEED TURN OFF MOTOR HERE.
	
	
	//update door open data with the time the door open finished, set our backup flag.
	off = true;
	_args = _data;
	_args.door_open_finish = _arduino->getTime();
	
	//trigger a final door open event, for logging
	EVENTHANDLER.trigger("Door opened", &_args);

	//now delete me - this shouldn't exist anymore...
	EVENTHANDLER.remove_eventAction(".1s",this);
}

SETUP_ACTION(doorman_close)
{
	EVENTHANDLER.add_event("Door closed");
}
EXECUTE_ACTION(doorman_close)
{
	DOOR_DATA* data = static_cast<DOOR_DATA*>(args);
	arduino_mega* arduino = static_cast<arduino_mega*>(trigger);

	_args.door_close_start = arduino->getTime();

	//close the door!
	data->door_to_close;

	_args.door_close_finish = arduino->getTime();
	


	EVENTHANDLER.trigger("Door closed", &_args);
}
