#include "HeaterActions.h"


void check_temperature::execute(EventArgs* args, void* trigger)
{
	avg_temp_args * tmpargs = static_cast<avg_temp_args*>(args);

	tmpargs->BNO_Temp;
	tmpargs->BMP_Temp;
	tmpargs->BNO_Temp;
}
