#include "HeaterActions.h"


void check_temperature::execute(EventArgs* args, void* trigger)
{
	avg_temp_args * tmpargs = static_cast<avg_temp_args*>(args);
	if (tmpargs->AVG_Temp < 0) {
		analogWrite(HeaterControl, 255);
	}
	else if (tmpargs->AVG_Temp >= 0) {
		analogWrite(HeaterControl, 0);
	}
	//tmpargs->BNO_Temp;
	//tmpargs->BMP_Temp;
	//tmpargs->AVG_Temp;
}
