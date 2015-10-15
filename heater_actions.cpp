#include "heater_actions.h"

ACTIONSETUP(update_heater_status) {
	pinMode(heater_control, OUTPUT);
	analogWrite(heater_control, 0);
}
ACTIONEXECUTE(update_heater_status) {
	avg_temp_args * temp_args = static_cast<avg_temp_args*>(args);
	if (temp_args->AVG_Temp < 0) analogWrite(heater_control, 50);
	else if (temp_args->AVG_Temp > 5) analogWrite(heater_control, 0);
}

//
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
