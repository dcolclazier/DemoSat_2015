#pragma once
#include "EventHandler.h"

struct update_heater_status : EventAction { 
	update_heater_status(); 
	void execute(EventArgs* args, void* trigger) override; 
private:  
	int heater_control = 3;
};
