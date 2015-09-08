#pragma once
#include "EventHandler.h"
#include "EventAction.h"
#include "LED.h"

class RedBoard {
public:
	RedBoard() {
		EventHandler::instance().add_eventAction(".1s", new OnboardLEDStatusFlash);
	}

private:

	ACTION(OnboardLEDStatusFlash) {
		EXECUTE(OnboardLEDStatusFlash);
		private: LED onboard;
	};
	
};
