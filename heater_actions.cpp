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

//Easy, right? If you want to create some variables that this action will remember for the whole flight, you can do it here as well:
CREATE_SIMPLEACTION(name_of_action)

	int somePinOnArduino = 3;
END_CREATE
//This syntax will look weird, but I haven't figured out a way to make it
// look nicer. DONT FORGET TO PUT END_CREATE at the end of your create macro.

//Once you create the action, you need two other macros: a setup, and an
//execute. The setup macro gets called when the action is created, once.
SETUP_SIMPLEACTION(name_of_action) {
	/*This is where you put code the action needs to run once, but not
	every time the action is executed. This can access stuff you created in
	the create_action macro:*/
	pinMode(somePinOnArduino, OUTPUT);
}
// The execute macro gets called every time the event that it is associated
// with triggers. For our event, this would happen every .1s.

EXECUTE_ACTION(name_of_action) {
	/*This is where you put code the action needs to execute
	every time it is triggered. 
	
	Now some events can send data with
	each trigger. The data is customized, and is inside a package called
	args. Let's say we want to turn the args into position data:*/
	position_args* data = static_cast<position_args*>(args);
	/*This only works if the event is sending a position_args package with the trigger - otherwise you'll get errors here.

	Now, I can do fun things with this data, like access the Euler Heading of our payload: */
	Serial.print(data->Euler.x());
	Serial.print(data->Euler.y());
	Serial.print(data->Euler.z());
	/*And I can access the Quaternian of the payload!*/
	Serial.print(data->Quat.x());
	Serial.print(data->Quat.y());
	Serial.print(data->Quat.z());
	Serial.print(data->Quat.w());
	
	//And I still have access to variables I created in the create macro.
	digitalWrite(somePinOnArduino, 255);
}

//Let's look at an actual action. First, hop over to heater_actions.h and
//look at the create macro.

//You looked? Good. Now, let's setup the action: All I'm doing in this case
//is telling the arduino that the pin to our heater is an output pin,
//and then I set its dutycycle (0 - 255, 0 being off) to 0.
SETUP_SIMPLEACTION(update_heater_status) {
	pinMode(heater_control, OUTPUT);
	analogWrite(heater_control, 0);
}

/*And here's my execute! It turns out this action is listening for an event named " avg_temp_update " that is triggered every 5 seconds. You can see that code in arduino_mega.cpp if you'd like!

First, we turn the "args" data into temperature data so we can access it.

Then, we have a bit of logic... If the average temp is less than 
0 degrees celcius, turn the heater on to 20% power. Otherwise, if the temperature is greater than 5 degrees celcius, turn the heater off.*/
EXECUTE_ACTION(update_heater_status) {
	temperature_args * temp_args = static_cast<temperature_args*>(args);
	
	if (temp_args->AVG_temp < 0) analogWrite(heater_control, 50);
	else if (temp_args->AVG_temp > 5) analogWrite(heater_control, 0);
}

