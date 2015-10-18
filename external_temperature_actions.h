#pragma once
#include "EventHandler.h"
#include <OneWire.h>
#include <DallasTemperature.h>

CREATE_EVENT_TRIGGERING_ACTION(get_external_temp, externalTemp_args)
//#define ONE_WIRE_BUS 2 //Assigns IC Bus to pin #2
OneWire oneWireBus;
DallasTemperature sensors;

END_CREATE


