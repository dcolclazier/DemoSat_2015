#include "heater_actions.h"
#include "EventAction.h"


//Let's look at an actual action. First, hop over to heater_actions.h and
//look at the create macro.

//You looked? Good. Now, let's setup the action: All I'm doing in this case
//is telling the arduino that the pin to our heater is an output pin,
//and then I set its dutycycle (0 - 255, 0 being off) to 0.
SETUP_ACTION(update_heater_status) {
	//Heater_control pin is 3, set to output?
	pinMode(heater_control, OUTPUT); 

	//Writing to the pin...
	analogWrite(heater_control, 0);
}

EXECUTE_ACTION(update_heater_status) {
	temperature_args * temp_args = static_cast<temperature_args*>(args);

	  if (temp_args->AVG_temp >= -8)analogWrite(heater_control, 0);
		//OFF
	  
	  else if (temp_args->AVG_temp <= -10 && temp_args->AVG_temp > -12.5) analogWrite(heater_control, 32);
		//MINIMUM

	  else if (temp_args->AVG_temp <= -12.5 && temp_args->AVG_temp > -15) analogWrite(heater_control, 64);
		//Level #2
	  
	  else if (temp_args->AVG_temp <= -15 && temp_args->AVG_temp > -17.5) analogWrite(heater_control, 96);
		//Level #3
	  
	  else if (temp_args->AVG_temp <= -17.5 && temp_args->AVG_temp > -20) analogWrite(heater_control, 128);
		//Level #4
	  
	  else if (temp_args->AVG_temp <= -20 && temp_args->AVG_temp > -22.5) analogWrite(heater_control, 160);
		//Level #5
	  
	  else if (temp_args->AVG_temp <= -22.5 && temp_args->AVG_temp > -25) analogWrite(heater_control, 192);
		//Level #6
	  
	  else if (temp_args->AVG_temp <= -25 && temp_args->AVG_temp > -27.5) analogWrite(heater_control, 224);
		//Level #7
	  
	  else if (temp_args->AVG_temp <= -27.5) analogWrite(heater_control, 255);
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

/*And here's my execute! It turns out this action is listening for an event named " avg_temp_update " that is triggered every 5 seconds. You can see that code in arduino_mega.cpp if you'd like!

First, we turn the "args" data into temperature data so we can access it.

Then, we have a bit of logic... If the average temp is less than 
0 degrees celcius, turn the heater on to 20% power. Otherwise, if the temperature is greater than 5 degrees celcius, turn the heater off.*/
 //EXECUTE_ACTION(update_heater_status) {
	//temperature_args * temp_args = static_cast<temperature_args*>(args);

	//if (temp_args->AVG_temp < 0) analogWrite(heater_control, 50);
	//else if (temp_args->AVG_temp > 5) analogWrite(heater_control, 0);
	//}
}
