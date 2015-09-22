#include "led_flash.h"
#include "Arduino.h"
#include "RTClib.h"

//Notice UNARYACTIONSETUP and UNARYACTIONINIT have identical signatures...
led_flash::led_flash(LED pin) : _pin(pin){}


//Just need the name of the class here.. You also have access to an (args) and a (trigger)
//args contains an object with the data you need, for instance - magnetic field data (see EventArgs.h)
//(trigger) may or may not contain the object that triggered the action
ACTIONEXECUTE(led_flash) {
	
	//Time* runTime = static_cast<Time*>(args);  //<-- time events contain current runTime as (args)
	_pin.toggle();
}

//Notice UNARYACTIONSETUP and UNARYACTIONINIT have identical signatures...
UNARYACTIONSETUP(print_time, RTC_DS1307 rtc) {
	_rtc = rtc;
}

ACTIONEXECUTE(print_time) {

	if (!_rtc.isrunning()) _rtc.adjust(DateTime(__DATE__, __TIME__));
	
	DateTime now = _rtc.now();
	Serial.print(now.year(), DEC);
	Serial.print(F("/"));
	Serial.print(now.month(), DEC);
	Serial.print(F("/"));
	Serial.print(now.day(), DEC);
	Serial.print(F(" "));
	Serial.print(now.hour(), DEC);
	Serial.print(F(":"));
	Serial.print(now.minute(), DEC);
	Serial.print(F(":"));
	Serial.print(now.second(), DEC);
	Serial.println();
	
		
}

