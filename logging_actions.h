#pragma once
#include "WString.h"
#include "EventHandler.h"
#include <SD.h>
#include "sd_shield.h"

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

SIMPLEUNARYACTION(log_bno_update, SD_Shield* logger)

File _logfile;
SD_Shield* _logger;
String _filename;
};

SIMPLEUNARYACTION(log_altitude_updatepdate, SD_Shield* logger)

File _logfile;
SD_Shield* _logger;
String _filename;
};
