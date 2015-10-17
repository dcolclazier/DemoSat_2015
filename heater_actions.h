#pragma once
#include "EventHandler.h"

//See? Easy-peasy! pick a name, don't forget the END_CREATE, and 
//create any variables I want the action to remember.
CREATE_SIMPLEACTION(update_heater_status) 
	int heater_control = 3;
END_CREATE
