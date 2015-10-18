#include "heater_actions.h"
#include "EventAction.h"


//Let's look at an actual action. First, hop over to heater_actions.h and
//look at the create macro.

//You looked? Good. Now, let's setup the action: All I'm doing in this case
//is telling the arduino that the pin to our heater is an output pin,
//and then I set its dutycycle (0 - 255, 0 being off) to 0.
SETUP_ACTION(update_heater_status) {
	//heater_control pin is 3, set to output?
	pinMode(heater_control, OUTPUT); 

	//writing to the pin..
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

