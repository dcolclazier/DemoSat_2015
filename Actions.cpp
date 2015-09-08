#include "Actions.h"


UNARYACTIONSETUP(LEDFlash, LED pin) {
	_pin = pin;
}

ACTIONEXECUTE(LEDFlash) {
	_pin.toggle();
}

