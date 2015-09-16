#pragma once
#include "EventAction.h"
#include "LED.h"

ACTION(led_flash) {
	UNARYACTIONINIT(led_flash, LED pin); // The name of the action, and any params it needs... This 
										// action needs an LED to toggle, meaning 1 paramater, so
										// we use the UNARYACTIONINIT.

private://just like you'd put in a class
	LED _pin;
};

