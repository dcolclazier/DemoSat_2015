
#include "external_temperature_actions.h"
#include "EventAction.h"

SETUP_SIMPLEACTION(get_external_temp) {
	sensors.begin();//Turn on all sensors on IC bus
}

EXECUTE_ACTION(get_external_temp) {
	temperature_args * temp_args = static_cast<temperature_args*>(args);

	sensors.requestTemperatures();//Request reading from probe
	temp_args->EXT_Temp = sensors.getTempCByIndex(0);//set temp argument "Ext_Temp" to probe reading
}

