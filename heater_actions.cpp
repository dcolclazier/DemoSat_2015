#include "heater_actions.h"
#include "EventAction.h"
//*************INSTRUCTIONS******************
//The start of the program sets up a clock, that triggers an "event" on different time intervals (.1s, 1s, 5s, etc.)

//The event handler works in the following way:
//	Add an event to the eventhandler, which allows you to trigger the event. You can add actions to the event, 
//	such that when the event is triggered, the action is performed.

//Now, let's say I want something to happen every .1s:
//The first thing I need to do is tell the EVENTHANDLER that there is an event:
	// EVENTHANDLER.add_event(".1s");

//Then, I set up a clock, such that every .1s, I trigger the event (don't worry about the clock logic)
//  There's actually 3 ways to trigger an event, but we'll look at the simple way first:
	// EVENTHANDLER.trigger(".1s");		


//That's it! Every .1s, this ".1s" event is triggered. Right now, nothing happens, because we haven't added an action to the event.
//Let's say I want to change that.. I need to add an action to the ".1s" event, which requires that I create an action.

//There are several ways to create an action - to start, we'll look at the easiest way:
	// CREATE_SIMPLEACTION(name_of_action);

//Easy, right? If you want to create some variables that this action will know about, you can do it here as well:
	// CREATE_SIMPLEACTION(name_of_action)
	// {
	//    int somePinOnArduino = 3;
	// }

//Once you create the action, you need two other macros: a setup, and an execute. The setup macro gets called when the action is created, once.
// The execute macro gets called every time the event that it is associated with triggers. For our event, this would happen every .1s.

//Each event can have an action associated with it.. For example: Every .1s, an event called ".1s" triggers
//	
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
	if (temp_args->avg_temp_update < 0) analogWrite(heater_control, 50);
	else if (temp_args->avg_temp_update > 5) analogWrite(heater_control, 0);
}

//OLD CODE
//void update_heater_status::execute(EventArgs* args, void* trigger)
//{
//	avg_temp_args * tmpargs = static_cast<avg_temp_args*>(args);
//	if (tmpargs->avg_temp_update < 0) {
//		analogWrite(HeaterControl, 50);
//	}
//	else if (tmpargs->avg_temp_update >= 0) {
//		analogWrite(HeaterControl, 0);
//	}
//	//tmpargs->BNO_Temp;
//	//tmpargs->BMP_Temp;
//	//tmpargs->avg_temp_update;
//}
