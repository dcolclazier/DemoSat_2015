#pragma once
#include "EventAction.h"
#include "LED.h"

ACTION(LEDFlash) {
	UNARYACTIONINIT(explicit LEDFlash, LED pin);
private:
	LED _pin;
};

