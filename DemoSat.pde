#include "EventHandler.h"
#include "Event.h"
#include "RedBoard.h"
#include "Arduino.h"
//#include "../../../../../Program Files (x86)/Arduino/hardware/arduino/avr/cores/arduino/Arduino.h"
int prevTime = 0;
int tickTime = 1;


void InitDevices() {
	//clock
	EventHandler::instance().add_event("1s", new Event());
	RedBoard mainBoard;

}

void setup() {
	InitDevices();
}

void loop() {
	unsigned long long int currentTime = millis() / 1000;
	if (currentTime - prevTime >= tickTime) {

		EventHandler::instance().trigger("1s", 0, 0);
		prevTime = currentTime;
	}
}
