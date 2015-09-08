#pragma once
#include "EventHandler.h"
#include "EventAction.h"
#include "LED.h"
#include "LEDFlash.h"

class RedBoard {
public:
	RedBoard() {
		_onboardLED = 13; //pin 13
		EventHandler::instance().add_eventAction(".1s", new LEDFlash(_onboardLED));
	}

private:
	LED _onboardLED;

};
