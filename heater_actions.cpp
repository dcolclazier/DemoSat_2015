#include "heater_actions.h"
//*************INSTRUCTIONS******************
//Every action gets a setup function and an execute macro.
//Match the name with the action name in sensor_actions.h

//SIMPLE - means that the action won't be triggering any new events, meaning we don't need a type_of_args_sent_with_trigger (see below)
//UNARY - means the action needs one piece of data from somewhere else in the program - could be a sensor, a component, w/e
//BINARY - means the action needs two pieces of data from somewhere else in the program 

// UNARYACTIONSETUP(name_of_action, piece_of_data){
//		put setup code here... if you're going to trigger an event, create that event here. 
//		Also assign your piece_of_data to the private variable you created for it.
// }

// BINARYACTIONSETUP(name_of_action, piece_of_data1, piece_of_data2){
//		put setup code here... if you're going to trigger an event, create that event here. 
//		Also assign your piece_of_data to the private variable you created for it.
// }

// ACTIONEXECUTE(name_of_action){
//		This is the code that runs when the action executes... for example, when the 
//		update_heater_status runs, it checks the average temperature and turns on/off the heater 
//		Another example would be the events below... They respond to a time event triggered in DemoSat.pde
//		and trigger another event containing data from the sensor.

//		One note: the first line of code turns the generic "args" into the args you need - into whatever args are sent with the 
//		event your action is responding to. You can copy/paste from another action until you get used to the syntax.
// }

SIMPLEACTIONSETUP(update_heater_status) {
	pinMode(heater_control, OUTPUT);
	analogWrite(heater_control, 0);
}
ACTIONEXECUTE(update_heater_status) {
	avg_temp_args * temp_args = static_cast<avg_temp_args*>(args);
	if (temp_args->AVG_Temp < 0) analogWrite(heater_control, 50);
	else if (temp_args->AVG_Temp > 5) analogWrite(heater_control, 0);
}

//OLD CODE
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
