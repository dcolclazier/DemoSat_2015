#pragma once
#include "EventHandler.h"
#include "EventAction.h"
#include "LED.h"

class RedBoard {
public:
	RedBoard() {
		EventHandler::instance().add_eventAction("1s", new OnboardLEDStatusFlash);
	}

private:

	ACTION(OnboardLEDStatusFlash) {

		OnboardLEDStatusFlash() {
			onboard = new LED(13);
		}
		EXECUTE{
			onboard->toggle();
		}
		private:
			LED* onboard;
	};




	
};
