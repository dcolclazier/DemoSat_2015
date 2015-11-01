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
		_matrix.drawRect(3, 3, 2, 2, LED_GREEN);
		break;
	case 2:
		_matrix.drawRect(3, 3, 2, 2, LED_YELLOW);
		break;
	case 1:
		_matrix.drawRect(3, 3, 2, 2, LED_RED);
		break;
	case 0:
		_matrix.drawRect(3, 3, 2, 2,  LED_RED);
		break;
	}
	switch (data->calib_accel)
	{
	case 3:
		_matrix.drawRect(2, 2, 4, 4, LED_GREEN);
		break;
	case 2:
		_matrix.drawRect(2, 2, 4, 4, LED_YELLOW);
		break;
	case 1:
		_matrix.drawRect(2, 2, 4, 4, LED_RED);
		break;
	case 0:
		_matrix.drawRect(2, 2, 4, 4, LED_RED);
		break;
	}
	switch (data->calib_gyro)
	{
	case 3:
		_matrix.drawRect(1, 1, 6, 6, LED_GREEN);
		break;
	case 2:
		_matrix.drawRect(1, 1, 6, 6, LED_YELLOW);
		break;
	case 1:
		_matrix.drawRect(1, 1, 6, 6, LED_RED);
		break;
	case 0:
		_matrix.drawRect(1, 1, 6, 6, LED_RED);
		break;
	}
	switch (data->calib_mag)
	{
	case 3:
		_matrix.drawRect(0, 0, 8, 8, LED_GREEN);
		break;
	case 2:
		_matrix.drawRect(0, 0, 8, 8, LED_YELLOW);
		break;
	case 1:
		_matrix.drawRect(0, 0, 8, 8, LED_RED);
		break;
	case 0:
		_matrix.drawRect(0, 0, 8, 8, LED_RED);
		break;
	}
	_matrix.writeDisplay();
}