#include "Doorman_Actions.h"
#include <Adafruit_MotorShield.h>
#include "EventHandler.h"
#include "arduino_mega.h"
SETUP_ACTION_2ARGS(doorman_altitude_check,
				   Adafruit_BMP085_Unified bmp,
				   arduino_mega* arduino)
	: _bmp(bmp), _arduino(arduino), door1(3, 2750, 2750), door2(2, 2750, 2750)
{}
EXECUTE_ACTION(doorman_altitude_check) {
	sensors_event_t event;
	float temp;
	_bmp.getEvent(&event);
	_bmp.getTemperature(&temp);
	float altitude = _bmp.pressureToAltitude(1012.8f, event.pressure);
	Serial.print("The doorman thinks the altitude is ");
	Serial.println(altitude);
	if(altitude > DOOR1_OPEN_ALT && door1.hasntbeenopenedbefore) {
		EVENTHANDLER.trigger("time to open", &door1, _arduino);
	}
	if(altitude > DOOR2_OPEN_ALT && door2.hasntbeenopenedbefore) {
		EVENTHANDLER.trigger("time to open", &door2, _arduino);
	}
	if(altitude > DOOR1_CLOSE_ALT && !door1.closed) {
		EVENTHANDLER.trigger("time to close", &door1, _arduino);
	}
	if(altitude > DOOR2_CLOSE_ALT && !door2.closed) {
		EVENTHANDLER.trigger("time to close", &door2, _arduino);
	}
	if(altitude < DOOR1_OPEN_ALT && !door1.closed && !door1.hasntbeenopenedbefore) {
		EVENTHANDLER.trigger("time to close", &door1, _arduino);
	}
	if(altitude < DOOR2_OPEN_ALT && !door2.closed && !door2.hasntbeenopenedbefore) {
		EVENTHANDLER.trigger("time to close", &door2, _arduino);
	}
	
}

SETUP_ACTION_1ARG(doorman_open, arduino_mega* arduino) : _arduino(arduino)
{

}

EXECUTE_ACTION(doorman_open)
{
	
	Door_Data* door = static_cast<Door_Data*>(args);
		
	if(door->closed & door->hasntbeenopenedbefore) {
		door->direction = FORWARD;
		door->hasntbeenopenedbefore = false;
		Serial.print("Opening door number: ");
		Serial.println(door->door_number);
		EVENTHANDLER.trigger("move door", door, _arduino);

	}
}

SETUP_ACTION_1ARG(doorman_close, arduino_mega* arduino) : _arduino(arduino)
{
	

}
EXECUTE_ACTION(doorman_close) {
	Door_Data* door = static_cast<Door_Data*>(args);
		
	if (!door->closed) {
		Serial.print("Closing door number: ");
		Serial.println(door->door_number);

		door->direction = BACKWARD;
		EVENTHANDLER.trigger("move door", door, _arduino);
	}
}

SETUP_ACTION_1ARG(turn_motor_on, arduino_mega* arduino) : _arduino(arduino){
}
EXECUTE_ACTION(turn_motor_on) {
	Door_Data * door = static_cast<Door_Data*>(args);
	

	if (door->moving) return;

	if (door->direction == FORWARD) door->door_open_start = _arduino->getTime();
	else if (door->direction == BACKWARD) door->door_close_start = _arduino->getTime();
	door->moving = true;

	Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
	Adafruit_DCMotor* motor = AFMS.getMotor(door->door_number);
	AFMS.begin();
	
	Serial.println("Turning on motor... vroom.");
	motor->run(door->direction);
	motor->setSpeed(MOTOR_FAST);

	door->door_start_millis = millis();
	door->motor_action = new turn_motor_off(door, _arduino);
	EVENTHANDLER.add_eventAction(".1s", door->motor_action);
}

SETUP_ACTION_2ARGS(turn_motor_off,
					Door_Data* door_data, 
				   arduino_mega* arduino) : door(door_data), _arduino(arduino) {}
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
	
	Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
	Adafruit_DCMotor* motor = AFMS.getMotor(door->door_number);

	Serial.println("Turning off motor... eeeerrrccheek!");

	if (door->direction == FORWARD) {
		motor->run(RELEASE);
		door->closed = false;
		door->door_open_finish = _arduino->getTime();
	}
	else if(door->direction == BACKWARD) {
		motor->setSpeed(MOTOR_SLOW);
		door->closed = true;
		door->door_close_finish = _arduino->getTime();
		door->hasntbeenopenedbefore = false;
	}
	

	//update door open data with the time the door open finished, set our backup flag.
	door->moving = false;

	EVENTHANDLER.trigger("sample collected", door);
	EVENTHANDLER.remove_eventAction(".1s", this);
}
