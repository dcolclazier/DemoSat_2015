#pragma once
#include <Arduino.h>
#include "EventData.h"
struct humidity_data : EventData {
	int Temp;
	int Humidity;
};
enum humid_sensor_mode {
	
};
class Sparkfun_Humid {
public:

	Sparkfun_Humid(int32_t address = -1);
	bool begin();
	uint8_t getHumidTemp(humidity_data& data);
private:
	uint8_t _address;
};
