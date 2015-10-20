#pragma once
#include "EventHandler.h"
//#include <OneWire.h>
#include <DallasTemperature.h>

CREATE_EVENT_TRIGGERING_ACTION(get_external_temp, externalTemp_args)

OneWire oneWireBus;
DallasTemperature sensors;

END_CREATE


