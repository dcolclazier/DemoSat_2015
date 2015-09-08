#include "RedBoard.h"

ACTIONSETUP(RedBoard, OnboardLEDStatusFlash) {
	onboard = LED(13); 
}

ACTIONEXECUTE(RedBoard, OnboardLEDStatusFlash) {
	onboard.toggle();
}