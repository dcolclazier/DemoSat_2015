#include "bmp_sensor_actions.h"
#include "EventHandler.h"

bmp_full_update::bmp_full_update(Adafruit_BMP085_Unified bmp) {
	_bmp = bmp;
	EVENTHANDLER.add_event("bmp_u", new Event);
}
void bmp_full_update::execute(EventArgs* args, void* trigger) {
	sensors_event_t event;
	_bmp.getEvent(&event);
	_args.Pressure = event.pressure;
	_bmp.getTemperature(&_args.Temp);
	_args.Altitude = _bmp.pressureToAltitude(_seaLevelPressure, event.pressure, _args.Temp);
	EVENTHANDLER.trigger("bmp_u", &_args, &_bmp);
}


avg_temp_update::avg_temp_update (Adafruit_BMP085_Unified bmp, Adafruit_BNO055 bno) : _bmp(bmp), _bno(bno)
{
	EVENTHANDLER.add_event("avg_tmp", new Event);
}

void avg_temp_update::execute(EventArgs* args, void* trigger)
{
	_bmp.getTemperature(&_args.BMP_Temp);
	_args.BNO_Temp = _bno.getTemp();
	_args.AVG_Temp = (_args.BNO_Temp + _args.BMP_Temp) / 2;
	EVENTHANDLER.trigger("avg_tmp", &_args, 0);
}
