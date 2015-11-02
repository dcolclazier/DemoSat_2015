#include <Arduino.h>
#include "UV_Sensor.h"

UV::UV(::uint8_t pin) : _UVSensorPin(pin)
{
	pinMode(_UVSensorPin, INPUT);
}

uint8_t UV::readUVB(){
	//analogRead(_UVSensorPin);

	float total = 0;
	for (int x = 0; x < 10; x++) {
		total += analogRead(_UVSensorPin);
	}
	total /= 10;

	return(total);
	
}

float UV::readUvVoltage(){

	float total = 0;
	for (int x = 0; x < 10; x++) {
		total += analogRead(_UVSensorPin);
	}
	total /= 10;

	float voltage = total * 4.9;

	return voltage;
}

uint8_t UV::readUVindex(){
	
	uint8_t UVindex = 0;
	uint8_t total = 0;
	for (int x = 0; x < 10; x++) 
	{
		total += analogRead(_UVSensorPin);
	}
	total /= 10;

	float voltage = total * 4.9;
	
	if (voltage >= 1170) UVindex = 11;

	if (voltage >= 1079 && voltage < 1170) UVindex = 10;

	if (voltage >= 976 && voltage < 1079) UVindex = 9;

	if (voltage >= 881 && voltage < 976) UVindex = 8;

	if (voltage >= 795 && voltage < 881) UVindex = 7;

	if (voltage >= 696 && voltage < 795) UVindex = 6;

	if (voltage >= 606 && voltage < 696) UVindex = 5;

	if (voltage >= 503 && voltage < 606) UVindex = 4;

	if (voltage >= 408 && voltage < 503) UVindex = 3;

	if (voltage >= 318 && voltage < 408) UVindex = 2;

	if (voltage >= 50 && voltage < 318) UVindex = 1;

	if (voltage < 50) UVindex = 0;

	return UVindex;

}