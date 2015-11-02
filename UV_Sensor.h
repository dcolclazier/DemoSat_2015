#pragma once
#include <Arduino.h>

class UV {

public:
	uint8_t readUVB();
	float readUvVoltage();
	uint8_t readUVindex();
	UV(uint8_t pin);
private:
	//uint8_t _UVSensorPin;
	uint8_t _UVSensorPin;
};