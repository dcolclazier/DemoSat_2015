#pragma once
#include "EventHandler.h"
#include <OneWire.h>
#include <DallasTemperature.h>

CREATE_SIMPLEACTION(get_external_temp)
#define ONE_WIRE_BUS 2 //Assigns IC Bus to pin #2
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any "OneWire" devices on the bus
DallasTemperature sensors(&oneWire); // Pass oneWire as reference to DallasTemperature
END_CREATE

