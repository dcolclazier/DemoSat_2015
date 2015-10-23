#include "Doorman_Actions.h"
#include <Adafruit_MotorShield.h>
#include "EventHandler.h"
#include "arduino_mega.h"
SETUP_ACTION_2ARGS(doorman_altitude_check,
				   Adafruit_BMP085_Unified bmp,
				   arduino_mega* arduino)
	: _bmp(bmp), _arduino(arduino), door1(1, 2380, 3000), door2(2, 3750, 3750), door3(3, 3750, 3750), door4(4, 3750, 3750)
{
	EVENTHANDLER.add_event("time to open");
	EVENTHANDLER.add_event("time to close");
	EVENTHANDLER.add_event("move door");
	EVENTHANDLER.add_event("door moved");

	EVENTHANDLER.add_eventAction("time to open", new doorman_open);
	EVENTHANDLER.add_eventAction("time to close", new doorman_close);
	EVENTHANDLER.add_eventAction("move door", new turn_motor_on);
}
EXECUTE_ACTION(doorman_altitude_check) {
	sensors_event_t event;
	float temp;
	_bmp.getEvent(&event);
	_bmp.getTemperature(&temp);
	float altitude = _bmp.pressureToAltitude(1012.8f, event.pressure);
	
	if (altitude > 1641.0f && altitude < 1844.0f) {
		if(!door1.moving && door1.closed) EVENTHANDLER.trigger("time to open", &door1, _arduino);
	}
	else if (altitude > 4000 && altitude < 4002) {
		if(!door2.moving && door2.closed) EVENTHANDLER.trigger("time to open", &door2, _arduino);
		if(!door1.moving && !door1.closed) EVENTHANDLER.trigger("time to close", &door1, _arduino);
	}
	else if (altitude > 6000 && altitude < 6002) {
		if(!door3.moving && door3.closed) EVENTHANDLER.trigger("time to open", &door3, _arduino);
		if(!door2.moving && !door2.closed) EVENTHANDLER.trigger("time to close", &door2, _arduino);
	}
	else if (altitude == 8000 && altitude < 8002) {
		if (!door4.moving && door4.closed) EVENTHANDLER.trigger("time to open", &door4, _arduino);
		if (!door3.moving && !door3.closed) EVENTHANDLER.trigger("time to close", &door3, _arduino);
	}
}

SETUP_ACTION(doorman_open){}
EXECUTE_ACTION(doorman_open)
{
	
	Door_Data* door = static_cast<Door_Data*>(args);
	arduino_mega* arduino = static_cast<arduino_mega*>(trigger);
	door->direction = FORWARD;
	Serial.print("Opening door number: ");
	Serial.println(door->door_number);
	if(door->closed) EVENTHANDLER.trigger("move door", door, arduino);
}

SETUP_ACTION(doorman_close) {}
EXECUTE_ACTION(doorman_close) {
	Door_Data* door = static_cast<Door_Data*>(args);
	arduino_mega* arduino = static_cast<arduino_mega*>(trigger);
	
	Serial.print("Closing door number: ");
	Serial.println(door->door_number);

	door->direction = BACKWARD;
	
	if (!door->closed) EVENTHANDLER.trigger("move door", door, arduino);
}

SETUP_ACTION(turn_motor_on) {
}
EXECUTE_ACTION(turn_motor_on) {
	Door_Data * door = static_cast<Door_Data*>(args);
	arduino_mega* arduino = static_cast<arduino_mega*>(trigger);
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	AFMS.begin();

	if (door->moving) return;

	if (door->direction == FORWARD) door->door_open_start = arduino->getTime();
	else if (door->direction == BACKWARD) door->door_close_start = arduino->getTime();
	door->moving = true;

		
	Adafruit_DCMotor *motor = AFMS.getMotor(door->door_number);
	
	Serial.println("Turning on motor... vroom.");
	motor->run(door->direction);
	motor->setSpeed(150);

	//turn on the motor for the door we're opening.
	door->door_number; // use this
	door->direction; // use this

	door->door_start_millis = millis();
	door->motor_action = new turn_motor_off(door, arduino);
	EVENTHANDLER.add_eventAction(".1s", door->motor_action);
}

SETUP_ACTION_2ARGS(turn_motor_off,
					Door_Data* door_data, 
				   const arduino_mega* arduino) : door(door_data), _arduino(arduino) {}
EXECUTE_ACTION(turn_motor_off) {
	//if we shouldn't turn off the motor, don't.
	
	unsigned long time = millis() - door->door_start_millis;
	Serial.print("motor runtime: ");
	Serial.println(time);
	switch (door->direction) {
	case FORWARD:
		if (time < door->openTime) return;
		break;
	case BACKWARD:
		if (time < door->closeTime) return;
		break;
	default: return;

	}
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	AFMS.begin();

	Adafruit_DCMotor *motor = AFMS.getMotor(door->door_number);

	Serial.println("Turning off motor... eeeerrrccheek!");
	motor->run(door->direction);
	motor->setSpeed(0);

	//update door open data with the time the door open finished, set our backup flag.
	door->moving = false;
	
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
	
	//now delete me - I shouldn't exist now.
	EVENTHANDLER.remove_eventAction(".1s", this);
}

