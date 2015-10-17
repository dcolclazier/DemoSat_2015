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

//BNO055 GYROSCOPE UPDATE - to trigger, use event name "gyro_update"
//args contains gyroscope data
UNARYACTION(gyro_update, gyro_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
};

//BNO055 MAGNETOMETER UPDATE - to trigger, use event name "magnetometer_update"
//args contain magnetometer data
UNARYACTION(magnetometer_update, magnetometer_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
};

//BNO055 GRAVITOMETER UPDATE - to trigger, use event name "gravitometer_update"
//args contain gravitometer data
UNARYACTION(gravitometer_update, gravitometer_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
};

//BNO055 ACCELERATION UPDATE - to trigger, use event name "accelerometer_update"
//args contain accelerometer and linear acceleration
UNARYACTION(accelerometer_update, accelerometer_args, Adafruit_BNO055 bno);
	Adafruit_BNO055 _bno;
};

//BNO055 POSITION UPDATE - to trigger, use event name "position_update"
//args contains both euler heading and quaternion
UNARYACTION(position_update, position_args, Adafruit_BNO055 bno);
	Adafruit_BNO055 _bno;
};

//BNO055 Full UPDATE - to trigger, use event name "bno_logger_update"
//args contains all possible data from bno_055 sensor 
//use this for logging data - it's memory intensive.
UNARYACTION(bno_logger_update, bno_logger_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
};

//BMP SENSOR UPDATE - to trigger, use event name "altitude_update"
//args contains temperature, pressure and altitude
UNARYACTION(altitude_update, altitude_args, Adafruit_BMP085_Unified bmp)

	Adafruit_BMP085_Unified _bmp;
	const float _seaLevelPressure = 1012.8f;
};

//AVG TEMP UPDATE - to trigger, use event name "avg_tmp"
//args contains temperature, pressure and altitude
BINARYACTION(avg_temp_update, avg_temp_args, Adafruit_BMP085_Unified bmp, Adafruit_BNO055 bno)
	
	Adafruit_BMP085_Unified _bmp;
	Adafruit_BNO055 _bno;
};