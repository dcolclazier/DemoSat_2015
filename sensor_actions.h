#pragma once
#include "EventHandler.h"
#include "Adafruit_BNO055.h"
#include "Adafruit_BMP085_U.h"

//Here are some newer actions still - they're called
// trigger actions. They work the same as the other actions,

/* with one big difference - they are responsible for triggering
 an event themselves. For instance - these actions respond to certain time intervals, grab data from the sensors, and then send that data in a new event trigger. 
 
 The thing you have to have for this is the correct 'type' of 
 data package. When we update the gyroscope, we fill up and send
 the gyro_data data package - it holds gyroscode data*/


//BNO055 GYROSCOPE UPDATE 
struct gyro_update : EventAction { 
	gyro_update(Adafruit_BNO055 bno); 
	void execute(EventArgs* args, void* trigger) override; 
private: 
	gyro_data _args ; 
	Adafruit_BNO055 _bno;
};

//BNO055 MAGNETOMETER UPDATE 
struct magnetometer_update : public EventAction { magnetometer_update(Adafruit_BNO055 bno); void execute(EventArgs* args, void* trigger) override; private: magnetometer_args _args ; 
	Adafruit_BNO055 _bno;
};

//BNO055 GRAVITOMETER UPDATE - to trigger, use event name "gravitometer_update"
//args contain gravitometer data
struct gravitometer_update : public EventAction { gravitometer_update(Adafruit_BNO055 bno); void execute(EventArgs* args, void* trigger) override; private: gravitometer_args _args ; 
	Adafruit_BNO055 _bno;
};

//BNO055 ACCELERATION UPDATE - to trigger, use event name "accelerometer_update"
//args contain accelerometer and linear acceleration
struct accelerometer_update : public EventAction { accelerometer_update(Adafruit_BNO055 bno); void execute(EventArgs* args, void* trigger) override; private: accelerometer_args _args ; ;
	Adafruit_BNO055 _bno;
};

//BNO055 POSITION UPDATE 
struct position_update : public EventAction { position_update(Adafruit_BNO055 bno); void execute(EventArgs* args, void* trigger) override; private: position_args _args ; ;
	Adafruit_BNO055 _bno;
};

//BNO055 Full UPDATE - to trigger, use event name "bno_logger_update"
//args contains all possible data from bno_055 sensors 
//use this for logging data - it's memory intensive.
struct bno_logger_update : public EventAction { bno_logger_update(Adafruit_BNO055 bno); void execute(EventArgs* args, void* trigger) override; private: bno_logger_data _args ; 
	Adafruit_BNO055 _bno;
};

//BMP SENSOR UPDATE - to trigger, use event name "altitude_update"
//args contains temperature, pressure and altitude
struct altitude_update : public EventAction { altitude_update(Adafruit_BMP085_Unified bmp); void execute(EventArgs* args, void* trigger) override; private: altitude_args _args ; 

	Adafruit_BMP085_Unified _bmp;
	const float _seaLevelPressure = 1012.8f;
};

//AVG TEMP UPDATE - to trigger, use event name "avg_tmp"
//args contains temperature, pressure and altitude
struct avg_temp_update : public EventAction { avg_temp_update(Adafruit_BMP085_Unified bmp, Adafruit_BNO055 bno); void execute(EventArgs* args, void* trigger) override; private: temperature_args _args ;
	
	Adafruit_BMP085_Unified _bmp;
	Adafruit_BNO055 _bno;
};