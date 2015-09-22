#pragma once
#include "EventAction.h"
#include "LED.h"
#include <RTClib.h>



ACTION(led_flash) {
	UNARYACTIONINIT(led_flash, LED pin); 

private:
	LED _pin;
};


ACTION(print_time) {
	UNARYACTIONINIT(print_time, RTC_DS1307 rtc);
private:
	RTC_DS1307 _rtc;
};
