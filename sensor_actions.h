#pragma once
#include "EventHandler.h"
#include "Adafruit_BNO055.h"
#include "Adafruit_BMP085_U.h"
//*************INSTRUCTIONS******************
//To create an action, follow the format below. A few notes:

//SIMPLE - means that the action won't be triggering any new events, meaning we don't need a type_of_args_sent_with_trigger (see below)
//UNARY - means the action needs one piece of data from somewhere else in the program - could be a sensor, a component, w/e
//BINARY - means the action needs two pieces of data from somewhere else in the program 

//The format is such:

// CREATE_TRIGGERACTION_ONE_ARG(action_name, type_of_args_sent_with_trigger, piece_of_data)
//		any private variables you plan on using with the action - you'll need one for the piece_of_data, like below...
// };

// CREATE_TRIGGERACTION_TWO_ARGS(action_name, type_of_args_sent_with_trigger, piece_of_data1, piece_of_data2)
//		any private variables you plan on using with the action - you'll need one for the piece_of_data, like below...
// };

// CREATE_SIMPLEACTION(action_name)
//		any private variables you plan on using with the action - you'll need one for the piece_of_data, like below...
// };

// CREATE_SIMPLEUNARYACTION(action_name, piece_of_data)
//		any private variables you plan on using with the action - you'll need one for the piece_of_data, like below...
// };

//BNO055 GYROSCOPE UPDATE - to trigger, use event name "gyro_update"
//args contains gyroscope data
CREATE_TRIGGERACTION_ONE_ARG(gyro_update, gyro_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
};

//BNO055 MAGNETOMETER UPDATE - to trigger, use event name "magnetometer_update"
//args contain magnetometer data
CREATE_TRIGGERACTION_ONE_ARG(magnetometer_update, magnetometer_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
};

//BNO055 GRAVITOMETER UPDATE - to trigger, use event name "gravitometer_update"
//args contain gravitometer data
CREATE_TRIGGERACTION_ONE_ARG(gravitometer_update, gravitometer_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
};

//BNO055 ACCELERATION UPDATE - to trigger, use event name "accelerometer_update"
//args contain accelerometer and linear acceleration
CREATE_TRIGGERACTION_ONE_ARG(accelerometer_update, accelerometer_args, Adafruit_BNO055 bno);
	Adafruit_BNO055 _bno;
};

//BNO055 POSITION UPDATE - to trigger, use event name "position_update"
//args contains both euler heading and quaternion
CREATE_TRIGGERACTION_ONE_ARG(position_update, position_args, Adafruit_BNO055 bno);
	Adafruit_BNO055 _bno;
};

//BNO055 Full UPDATE - to trigger, use event name "bno_logger_update"
//args contains all possible data from bno_055 sensor 
//use this for logging data - it's memory intensive.
CREATE_TRIGGERACTION_ONE_ARG(bno_logger_update, bno_logger_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
};

//BMP SENSOR UPDATE - to trigger, use event name "altitude_update"
//args contains temperature, pressure and altitude
CREATE_TRIGGERACTION_ONE_ARG(altitude_update, altitude_args, Adafruit_BMP085_Unified bmp)

	Adafruit_BMP085_Unified _bmp;
	const float _seaLevelPressure = 1012.8f;
};

//AVG TEMP UPDATE - to trigger, use event name "avg_tmp"
//args contains temperature, pressure and altitude
CREATE_TRIGGERACTION_TWO_ARGS(avg_temp_update, temperature_args, Adafruit_BMP085_Unified bmp, Adafruit_BNO055 bno)
	
	Adafruit_BMP085_Unified _bmp;
	Adafruit_BNO055 _bno;
};