#pragma once
#include "EventHandler.h"
#include <Adafruit_BMP085_U.h>

struct bmp_full_update : public EventAction  {
	bmp_full_update(Adafruit_BMP085_Unified bmp); 
	void execute(EventArgs* args, void* trigger) override;
private:
	Adafruit_BMP085_Unified _bmp;
	bmp_full_args _args;
	const float _seaLevelPressure = 1012.8f;
};

struct avg_temp_update : public EventAction
{
	avg_temp_update(Adafruit_BMP085_Unified bmp, Adafruit_BNO055 bno);
	void execute(EventArgs* args, void* trigger) override;

private:
	avg_temp_args _args;
	Adafruit_BMP085_Unified _bmp;
	Adafruit_BNO055 _bno;
};