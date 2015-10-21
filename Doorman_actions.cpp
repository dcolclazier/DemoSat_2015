#include "Doorman_Actions.h"
#include "EventHandler.h"
#include "arduino_mega.h"
SETUP_ACTION_TWO_ARGS(doorman_altitude_check, Adafruit_BMP085_Unified bmp, arduino_mega* arduino)
{
	_bmp = bmp;
	_arduino = arduino;
	EVENTHANDLER.add_event("open door");
	EVENTHANDLER.add_event("close door");
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

	//open the door


	data->door_to_open;
	
	
	
	_args.door_open_finish = arduino->getTime();
	EVENTHANDLER.trigger("Door opened", &_args);
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

EXECUTE_ACTION(doorman_altitude_check)
{
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
		EVENTHANDLER.trigger("open door", &_args, &_arduino);
	}


}