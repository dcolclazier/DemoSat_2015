#pragma once
#include "EventHandler.h"
#include "Adafruit_BNO055.h"
#include "Adafruit_BMP085_U.h"
#include "HIH6130.h"
#include "DallasTemperature.h"



CREATE_EVENT_TRIGGERING_ACTION_1ARG(new_sensor_update, new_sensor_data, const SensorPackage& sensors)
SensorPackage _sensors;
float _seaLevelPressure = 1012.8; 
END_CREATE

CREATE_EVENT_TRIGGERING_ACTION_1ARG(external_temp_update, external_temp, const DallasTemperature& external_temperature)

DallasTemperature _Ext_temp;

END_CREATE

CREATE_EVENT_TRIGGERING_ACTION_3ARGS(avg_temp_update, temperature_data, const Adafruit_BMP085_Unified& bmp, const Adafruit_BNO055& bno, const HIH6130& humid)

	HIH6130 _humid;
	Adafruit_BMP085_Unified _bmp;
	Adafruit_BNO055 _bno;
END_CREATE