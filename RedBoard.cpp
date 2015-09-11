#include "RedBoard.h"

RedBoard::RedBoard() {
	_onboardLED = 13; //pin 13
	_bnoSensor = 55; //I2C address 0x55

	EVENTHANDLER.add_eventAction(".1s", new LEDFlash(_onboardLED));
	EVENTHANDLER.add_eventAction(".1s", new BNOTest(_bnoSensor));
}