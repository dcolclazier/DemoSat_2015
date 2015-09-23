#include "bmp_sensor_actions.h"
#include "EventHandler.h"

UNARYACTIONSETUP(bmp_full_update, Adafruit_BMP085_Unified  bmp) {
	_bmp = bmp;
	EVENTHANDLER.add_event("bmp_u", new Event);
}
ACTIONEXECUTE(bmp_full_update) {
	sensors_event_t event;
	_bmp.getEvent(&event);
	_args.Pressure = event.pressure;
	_bmp.getTemperature(&_args.Temp);
	_args.Altitude = _bmp.pressureToAltitude(_seaLevelPressure, event.pressure, _args.Temp);
	EVENTHANDLER.trigger("bmp_u", &_args, &_bmp);
}

