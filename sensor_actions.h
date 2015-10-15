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

// SIMPLEACTION(action_name)
//		any private variables you plan on using with the action - you'll need one for the piece_of_data, like below...
// };

// SIMPLEUNARYACTION(action_name, piece_of_data)
//		any private variables you plan on using with the action - you'll need one for the piece_of_data, like below...
// };

//BNO055 GYROSCOPE UPDATE - to trigger, use event name "bn_gy_u"
//args contains gyroscope data
UNARYACTION(bno_gyro_update, bno_gyro_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
};

//BNO055 MAGNETOMETER UPDATE - to trigger, use event name "bn_m_u"
//args contain magnetometer data
UNARYACTION(bno_mag_update, bno_mag_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
};

//BNO055 GRAVITOMETER UPDATE - to trigger, use event name "bn_gr_u"
//args contain gravitometer data
UNARYACTION(bno_grav_update, bno_grav_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
};

//BNO055 ACCELERATION UPDATE - to trigger, use event name "bn_a_u"
//args contain accelerometer and linear acceleration
UNARYACTION(bno_accel_update, bno_accel_args, Adafruit_BNO055 bno);
	Adafruit_BNO055 _bno;
};

//BNO055 POSITION UPDATE - to trigger, use event name "bn_p_u"
//args contains both euler heading and quaternion
UNARYACTION(bno_position_update, bno_position_args, Adafruit_BNO055 bno);
	Adafruit_BNO055 _bno;
};

//BNO055 Full UPDATE - to trigger, use event name "bn_full_u"
//args contains all possible data from bno_055 sensor 
//use this for logging data - it's memory intensive.
UNARYACTION(bno_full_update, bno_full_args, Adafruit_BNO055 bno)
	Adafruit_BNO055 _bno;
};

//BMP SENSOR UPDATE - to trigger, use event name "alt_u"
//args contains temperature, pressure and altitude
UNARYACTION(altitude_sensor_update, bmp_full_args, Adafruit_BMP085_Unified bmp)

	Adafruit_BMP085_Unified _bmp;
	const float _seaLevelPressure = 1012.8f;
};

//AVG TEMP UPDATE - to trigger, use event name "avg_tmp"
//args contains temperature, pressure and altitude
BINARYACTION(avg_temp_update, avg_temp_args, Adafruit_BMP085_Unified bmp, Adafruit_BNO055 bno)
	
	Adafruit_BMP085_Unified _bmp;
	Adafruit_BNO055 _bno;
};