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
	float altitude = _bmp.pressureToAltitude(1012.8f, event.pressure);



	if (altitude > 1641.0f && altitude < 1644.0f) {
		if(!door1.moving) EVENTHANDLER.trigger("time to open", &door1, _arduino);
	}
	else if (altitude > 4000 && altitude < 4002) {
		if(!door2.moving) EVENTHANDLER.trigger("time to open", &door2, _arduino);
		if(!door1.moving) EVENTHANDLER.trigger("time to close", &door1, _arduino);
	}
	else if (altitude > 6000 && altitude < 6002) {
		if(!door3.moving) EVENTHANDLER.trigger("time to open", &door3, _arduino);
		if(!door2.moving) EVENTHANDLER.trigger("time to close", &door1, _arduino);
	}
	else if (altitude == 8000 && altitude < 8002) {
		if (!door4.moving) EVENTHANDLER.trigger("time to open", &door4, _arduino);
		if (!door3.moving) EVENTHANDLER.trigger("time to close", &door3, _arduino);
	}
	else {
		/*Serial.print("not ready yet: altitude = ");
		Serial.print(altitude);
		Serial.println();*/
	}
	

}
SETUP_ACTION(doorman_open){}
EXECUTE_ACTION(doorman_open)
{
	
	Door_Data* door = static_cast<Door_Data*>(args);
	arduino_mega* arduino = static_cast<arduino_mega*>(trigger);
	door->direction = FORWARD;
	//door->moving = true;
	Serial.print("Opening door number: ");
	Serial.println(door->door_number);
	if(door->closed) EVENTHANDLER.trigger("move door", door, arduino);
	else;// Serial.println("door already open!");
}

SETUP_ACTION(doorman_close) {}
EXECUTE_ACTION(doorman_close) {
	Door_Data* door = static_cast<Door_Data*>(args);
	arduino_mega* arduino = static_cast<arduino_mega*>(trigger);
	
	Serial.print("Closing door number: ");
	Serial.println(door->door_number);

	door->direction = BACKWARD;
	
	if (!door->closed) EVENTHANDLER.trigger("move door", door, arduino);
	else; Serial.println("door already closed!");
}


SETUP_ACTION(move_door) : _args(0) {}
EXECUTE_ACTION(move_door) {
	Door_Data * door = static_cast<Door_Data*>(args);
	arduino_mega* arduino = static_cast<arduino_mega*>(trigger);
	if (door->moving) return;

	if (door->direction == FORWARD) door->door_open_start = arduino->getTime();
	else if (door->direction == BACKWARD) door->door_close_start = arduino->getTime();
	door->moving = true;

	Serial.println("Turning on motor... vroom.");

	//turn on the motor for the door we're opening.
	door->door_number; // use this
	door->direction; // use this

	door->door_start_millis = millis();
	_args.motor_action = new motor_on(door, arduino);
	EVENTHANDLER.add_eventAction(".1s", _args.motor_action);
}



SETUP_ACTION_2ARGS(motor_on, Door_Data* door_data, const arduino_mega* arduino) :_args(0), door(door_data), _arduino(arduino) {}
EXECUTE_ACTION(motor_on) {
	//if we shouldn't turn off the motor, don't.
	//if (off) return;
	unsigned long time = millis() - door->door_start_millis;
	Serial.print("motor runtime: ");
	Serial.println(time);
	if (time < door->runTime) return;

	//turn off motor 
	//NEED TURN OFF MOTOR HERE.
	door->door_number; //use this
	door->direction; // use this
	Serial.println("Turning off motor... eeeerrrccheek!");
	//update door open data with the time the door open finished, set our backup flag.
	door->moving = false;
	
	off = true;
	if(door->direction ==FORWARD) {
		door->closed = false;
		door->door_open_finish = _arduino->getTime();
	}
	else if (door->direction == BACKWARD) {
		door->closed = true;
		door->door_close_finish = _arduino->getTime();
	}
	
	door->closed = false;
	//trigger a final door event, for logging purposes
	EVENTHANDLER.trigger("door moved", door);
	
	//now delete me - I shouldn't exist now.. but even if I don't get deleted, we should be good.
	EVENTHANDLER.remove_eventAction(".1s", this);
}

