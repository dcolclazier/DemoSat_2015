#include "Doorman_Actions.h"
#include <Adafruit_MotorShield.h>
#include "EventHandler.h"
#include "arduino_mega.h"
SETUP_ACTION_2ARGS(doorman_altitude_check, Adafruit_BMP085_Unified bmp, arduino_mega* arduino) : _bmp(bmp), _arduino(arduino), door1(1), door2(2), door3(3), door4(4)
{
	EVENTHANDLER.add_event("time to open");
	EVENTHANDLER.add_event("time to close");
	EVENTHANDLER.add_event("move door");
	EVENTHANDLER.add_event("door moved");

	EVENTHANDLER.add_eventAction("time to open", new doorman_open);
	EVENTHANDLER.add_eventAction("time to close", new doorman_close);
	EVENTHANDLER.add_eventAction("move door", new move_door);
}

EXECUTE_ACTION(doorman_altitude_check) {
	sensors_event_t event;
	float temp;
	_bmp.getEvent(&event);
	_bmp.getTemperature(&temp);
	float altitude = _bmp.pressureToAltitude(1012.8f, event.pressure, temp);


	if (altitude > 2000 && altitude < 2002) {
		if(!door1.moving) EVENTHANDLER.trigger("time to open", &door1, &_arduino);
	}
	if (altitude > 4000 && altitude < 4002) {
		if(!door2.moving) EVENTHANDLER.trigger("time to open", &door2, &_arduino);
		if(!door1.moving) EVENTHANDLER.trigger("time to close", &door1, &_arduino);
	}
	if (altitude > 6000 && altitude < 6002) {
		if(!door3.moving) EVENTHANDLER.trigger("time to open", &door3, &_arduino);
		if(!door2.moving) EVENTHANDLER.trigger("time to close", &door1, &_arduino);
	}
	if (altitude == 8000 && altitude < 8002) {
		if (!door4.moving) EVENTHANDLER.trigger("time to open", &door4, &_arduino);
		if (!door3.moving) EVENTHANDLER.trigger("time to close", &door3, &_arduino);
	}


}
SETUP_ACTION(doorman_open){}
EXECUTE_ACTION(doorman_open)
{
	Door_Data* data = static_cast<Door_Data*>(args);
	data->direction = FORWARD;
	EVENTHANDLER.trigger("move_door", data);
}

SETUP_ACTION(doorman_close) {}
EXECUTE_ACTION(doorman_close) {
	Door_Data* data = static_cast<Door_Data*>(args);
	data->direction = BACKWARD;
	EVENTHANDLER.trigger("move_door", data);
}


SETUP_ACTION(move_door) : _args(0) {}
EXECUTE_ACTION(move_door) {
	Door_Data * door = static_cast<Door_Data*>(args);
	arduino_mega* arduino = static_cast<arduino_mega*>(trigger);
	door->door_open_start = arduino->getTime();
	door->moving = true;
	//turn on the motor for the door we're opening.
	door->door_number; // use this
	door->direction; // use this


	_args.motor_action = new motor_on(door, arduino);
	EVENTHANDLER.add_eventAction(".1s", _args.motor_action);
}



SETUP_ACTION_2ARGS(motor_on, Door_Data* data, const arduino_mega* arduino) :_args(0), _data(data), _arduino(arduino) {}
EXECUTE_ACTION(motor_on) {
	//if we shouldn't turn off the motor, don't.
	if (millis() - _data->door_start_millis < motor_run_time) return;
	if (off) return;

	//turn off motor 
	//NEED TURN OFF MOTOR HERE.
	_data->moving = false;
	_data->door_number; //use this
	_data->direction; // use this
	
	//update door open data with the time the door open finished, set our backup flag.
	off = true;
	if(_data->direction ==FORWARD) _data->door_open_finish = _arduino->getTime();
	else if (_data->direction == BACKWARD) _data->door_close_finish = _arduino->getTime();
	
	//trigger a final door event, for logging purposes
	EVENTHANDLER.trigger("door moved", _data);

	//now delete me - this shouldn't exist anymore...
	EVENTHANDLER.remove_eventAction(".1s",this);
}

