#include "Matrix_actions.h"



SETUP_ACTION_1ARG(update_config_status, Adafruit_BicolorMatrix bicolor) : _matrix(bicolor)
{
	//_matrix.drawPixel(0, 0, 0);
	_matrix.clear();
}

EXECUTE_ACTION(update_config_status)
{
	
	config_data * data = static_cast<config_data*>(args);
	_matrix.clear();
	switch(data->calib_system)
	{
	case 3:
		_matrix.drawPixel(0, 0, LED_GREEN);
		break;
	case 2:
		_matrix.drawPixel(0, 0, LED_YELLOW);
		break;
	case 1:
		_matrix.drawPixel(0, 0, LED_RED);
		break;
	case 0:
		_matrix.drawPixel(0, 0, LED_RED);
		break;
	}
	switch (data->calib_accel)
	{
	case 3:
		_matrix.drawPixel(0, 1, LED_GREEN);
		break;
	case 2:
		_matrix.drawPixel(0, 1, LED_YELLOW);
		break;
	case 1:
		_matrix.drawPixel(0, 1, LED_RED);
		break;
	case 0:
		_matrix.drawPixel(0, 1, LED_RED);
		break;
	}
	switch (data->calib_gyro)
	{
	case 3:
		_matrix.drawPixel(0, 2, LED_GREEN);
		break;
	case 2:
		_matrix.drawPixel(0, 2, LED_YELLOW);
		break;
	case 1:
		_matrix.drawPixel(0, 2, LED_RED);
		break;
	case 0:
		_matrix.drawPixel(0, 2, LED_RED);
		break;
	}
	switch (data->calib_mag)
	{
	case 3:
		_matrix.drawPixel(0, 3, LED_GREEN);
		break;
	case 2:
		_matrix.drawPixel(0, 3, LED_YELLOW);
		break;
	case 1:
		_matrix.drawPixel(0, 3, LED_RED);
		break;
	case 0:
		_matrix.drawPixel(0, 3, LED_RED);
		break;
	}
	_matrix.writeDisplay();
}