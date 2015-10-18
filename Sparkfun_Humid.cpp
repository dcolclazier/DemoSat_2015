#include "Sparkfun_Humid.h"
#include "Wire.h"
Sparkfun_Humid::Sparkfun_Humid(int32_t sensorID) {
	
}

bool Sparkfun_Humid::begin() {
	
}

uint8_t Sparkfun_Humid::getHumidTemp(humidity_data& data) {
	
	Wire.beginTransmission(_address);
	Wire.endTransmission();
	Wire.requestFrom(_address, 4);
	uint8_t Hum_H = Wire.read();
	uint8_t Hum_L = Wire.read();
	uint8_t Temp_H = Wire.read();
	uint8_t Temp_L = Wire.read();
	Wire.endTransmission();
	
	uint8_t status = (Hum_H >> 6) & 0x03;
	Hum_H = Hum_H & 0x3f;
	data.Humidity = ((unsigned int)Hum_H << 8 | Hum_L)*6.10e-3;
	data.Temp = ((unsigned int)Temp_H << 8 | Temp_L) * 1.007e-2 - 40;
	return status;
}