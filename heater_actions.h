#pragma once
#include "EventHandler.h"

//*************INSTRUCTIONS******************
//To create an action, follow the format below. A few notes:

//SIMPLE - means that the action won't be triggering any new events, meaning we don't need a type_of_args_sent_with_trigger (see below)
//UNARY - means the action needs one piece of data from somewhere else in the program - could be a sensor, a component, w/e
//BINARY - means the action needs two pieces of data from somewhere else in the program 

//The format is such:

// UNARYACTION(action_name, type_of_args_sent_with_trigger, piece_of_data)
//		any private variables you plan on using with the action - you'll need one for the piece_of_data, like below...
// };

// BINARYACTION(action_name, type_of_args_sent_with_trigger, piece_of_data1, piece_of_data2)
//		any private variables you plan on using with the action - you'll need one for the piece_of_data, like below...
// };

// CREATE_SIMPLEACTION(action_name)
//		any private variables you plan on using with the action - you'll need one for the piece_of_data, like below...
// };

// SIMPLEUNARYACTION(action_name, piece_of_data)
//		any private variables you plan on using with the action - you'll need one for the piece_of_data, like below...
// };

CREATE_SIMPLEACTION(update_heater_status) 
	int heater_control = 11;
};

//OLD CODE
//struct update_heater_status : public EventAction
//{
//	//update_heater_status(const HeaterController& ctrl) : _controller(ctrl) {}
//	update_heater_status() {
//		pinMode(HeaterControl, OUTPUT);
//		analogWrite(HeaterControl, 0);
//	}
//	void execute(EventArgs* args, void* trigger) override;
//private:
//	//HeaterController _controller;
//	int HeaterControl = 11;
//	
//};