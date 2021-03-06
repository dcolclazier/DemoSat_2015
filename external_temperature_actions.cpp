
#include "external_temperature_actions.h"
#include "EventAction.h"

SETUP_ACTION(get_external_temp) : oneWireBus(OneWire(2)), sensors(&oneWireBus) {
	EVENTHANDLER.add_event("external_temp_update");
	sensors.begin();//Turn on all sensors on IC bus
}

EXECUTE_ACTION(get_external_temp) {

	sensors.requestTemperatures();//Request reading from probe
	_args.EXT_Temp = sensors.getTempCByIndex(0);
	EVENTHANDLER.trigger("external_temp_update", &_args);
}

