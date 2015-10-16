#include "heater_actions.h"

SIMPLEACTIONSETUP(update_heater_status) {
	pinMode(heater_control, OUTPUT);
	analogWrite(heater_control, 0);
}
ACTIONEXECUTE(update_heater_status) {
	avg_temp_args * temp_args = static_cast<avg_temp_args*>(args);

	  if (temp_args->AVG_Temp >= -8)analogWrite(heater_control, 0);
		//OFF
	  
	  else if (temp_args->AVG_Temp <= -10 && temp_args->AVG_Temp > -12.5) analogWrite(heater_control, 32);
		//MINIMUM

	  else if (temp_args->AVG_Temp <= -12.5 && temp_args->AVG_Temp > -15) analogWrite(heater_control, 64);
		//Level #2
	  
	  else if (temp_args->AVG_Temp <= -15 && temp_args->AVG_Temp > -17.5) analogWrite(heater_control, 96);
		//Level #3
	  
	  else if (temp_args->AVG_Temp <= -17.5 && temp_args->AVG_Temp > -20) analogWrite(heater_control, 128);
		//Level #4
	  
	  else if (temp_args->AVG_Temp <= -20 && temp_args->AVG_Temp > -22.5) analogWrite(heater_control, 160);
		//Level #5
	  
	  else if (temp_args->AVG_Temp <= -22.5 && temp_args->AVG_Temp > -25) analogWrite(heater_control, 192);
		//Level #6
	  
	  else if (temp_args->AVG_Temp <= -25 && temp_args->AVG_Temp > -27.5) analogWrite(heater_control, 224);
		//Level #7
	  
	  else if (temp_args->AVG_Temp <= -27.5) analogWrite(heater_control, 255);
		//MAXIMUM
	  
//
//if (temp_args->AVG_Temp < 0) analogWrite(heater_control, 50);
//else if (temp_args->AVG_Temp > 5) analogWrite(heater_control, 0);
//void update_heater_status::execute(EventArgs* args, void* trigger)
//{
//	avg_temp_args * tmpargs = static_cast<avg_temp_args*>(args);
//	if (tmpargs->AVG_Temp < 0) {
//		analogWrite(HeaterControl, 50);
//	}
//	else if (tmpargs->AVG_Temp >= 0) {
//		analogWrite(HeaterControl, 0);
//	}
//	//tmpargs->BNO_Temp;
//	//tmpargs->BMP_Temp;
//	//tmpargs->AVG_Temp;
//}
