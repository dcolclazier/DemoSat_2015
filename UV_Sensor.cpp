#include <Arduino.h>
#include "UV_Sensor.h"

UV::UV(::uint8_t pin) : _UVSensorPin(pin)
{
	pinMode(_UVSensorPin, INPUT);
}

uint8_t UV::readUV(){
	//analogRead(_UVSensorPin);

	float total = 0;
	for (int x = 0; x < 10; x++) {
		total += analogRead(_UVSensorPin);
	}
	total /= 10;

	return(total);
	
}

float UV::readVoltage(){

	float total = 0;
	for (int x = 0; x < 10; x++) {
		total += analogRead(_UVSensorPin);
	}
	total /= 10;

	float voltage = total * 4.9;

	return voltage;
}