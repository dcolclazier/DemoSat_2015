#include "Doorman_Actions.h"
#include "EventHandler.h"

SETUP_ACTION_ONE_ARG(doorman_altitude_check, Adafruit_BMP085_Unified bmp)
{
	_bmp = bmp;
	EVENTHANDLER.add_event("open door");
	EVENTHANDLER.add_event("close door");
}

SETUP_ACTION(doorman_open)
{
	
}

EXECUTE_ACTION(doorman_open)
{
	
}

SETUP_ACTION(doorman_close)
{
	
}
EXECUTE_ACTION(doorman_close)
{
	
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
		EVENTHANDLER.trigger("open door", &_args);
	}
	if (altitude == 5000) {
		_args.door_to_open = 2;
		_args.door_to_close = 1;
		EVENTHANDLER.trigger("open door", &_args);
		EVENTHANDLER.trigger("close door", &_args);
	}
	if (altitude == 10000) {
		_args.door_to_open = 3;
		EVENTHANDLER.trigger("open door", &_args);
	}


}