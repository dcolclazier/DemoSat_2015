#include "heater_actions.h"
#include "EventAction.h"
#include "EventData.h"

//Let's look at an actual action. First, hop over to heater_actions.h and
//look at the create macro.

//You looked? Good. Now, let's setup the action: All I'm doing in this case
//is telling the arduino that the pin to our heater is an output pin,
//and then I set its dutycycle (0 - 255, 0 being off) to 0.
SETUP_ACTION(update_heater_status){
	//Heater_control pin is 3, set to output?
	pinMode(heater_control, OUTPUT); 

	//Writing to the pin...
	analogWrite(heater_control, 0);
}

EXECUTE_ACTION(update_heater_status) {
	temperature_data * temp_args = static_cast<temperature_data*>(args);
	float temp = temp_args->AVG_temp;

	  if (temp >= -8)	analogWrite(heater_control, 0);
		//OFF
	  
	  else if (temp <= -10 && temp > -12.5) analogWrite(heater_control, 32);
		//MINIMUM

	  else if (temp <= -12.5 && temp > -15) analogWrite(heater_control, 64);
		//Level #2
	  
	  else if (temp <= -15 && temp > -17.5) analogWrite(heater_control, 96);
		//Level #3
	  
	  else if (temp <= -17.5 && temp > -20) analogWrite(heater_control, 128);
		//Level #4
	  
	  else if (temp <= -20 && temp > -22.5) analogWrite(heater_control, 160);
		//Level #5
	  
	  else if (temp <= -22.5 && temp > -25) analogWrite(heater_control, 192);
		//Level #6
	  
	  else if (temp <= -25 && temp > -27.5) analogWrite(heater_control, 224);
		//Level #7
	  
	  else if (temp <= -27.5) analogWrite(heater_control, 255);
		//MAXIMUM
	
}
