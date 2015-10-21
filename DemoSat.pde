#include "EventHandler.h"
#include "EventArgs.h"
#include "Event.h"
#include "arduino_mega.h"
#include <Arduino.h>
#include <avr/wdt.h>

#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include <Adafruit_BMP085_U.h>
#include <SPI.h>
#include <RTClib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SD.h>
#include "sd_shield.h"
//*************INSTRUCTIONS******************
//The start of the program sets up a clock, that triggers an "event" on different time intervals (.1s, 1s, 5s, etc.)

//The event handler works in the following way:
//	Add an event to the eventhandler, which allows you to trigger the event. You can add actions to the event, 
//	such that when the event is triggered, the action is performed.

//Now, let's say I want something to happen every .1s:
//The first thing I need to do is tell the EVENTHANDLER that there is an event:
// EVENTHANDLER.add_event(".1s");

//Then, I set up a clock, such that every .1s, I trigger the event (don't worry about the clock logic) ".1s"
//  There's actually 3 ways to trigger an event, but we'll look at the simple way first:
// EVENTHANDLER.trigger(".1s");		


//That's it! Every .1s, this ".1s" event is triggered. Right now, nothing happens, because we haven't added an action to the event.
//Let's say I want to change that.. I need to add an action to the ".1s" event, which requires that I create an action.

//There are several ways to create an action - to start, we'll look at the easiest way:

//Easy, right? If you want to create some variables that this action will remember for the whole flight, you can do it here as well:

//CREATE_ACTION(name_of_action)
//
//	int _somePinOnArduino = 3;
//END_CREATE

//This syntax will look weird, but I haven't figured out a way to make it
// look nicer. DONT FORGET TO PUT END_CREATE at the end of your create macro.

//Once you create the action, you need two other macros: a setup, and an
//execute. The setup macro gets called when the action is created, once.

//SETUP_ACTION(name_of_action) {
	/*This is where you put code the action needs to run once, but not
	every time the action is executed. This can access stuff you created in
	the create_action macro:*/
	//EVENTHANDLER.add_eventAction(".1s", name_of_action);
	//pinMode(_somePinOnArduino, OUTPUT);
	
//}

// The execute macro gets called every time the event that it is associated
// with triggers. For our event, this would happen every .1s.



void InitClock() {

	EVENTHANDLER.add_event(".1s");
	EVENTHANDLER.add_event(".5s");
	EVENTHANDLER.add_event("1s");
	EVENTHANDLER.add_event("5s");
	EVENTHANDLER.add_event("10s");
	EVENTHANDLER.add_event("15s");
	EVENTHANDLER.add_event("30s");
	EVENTHANDLER.add_event("1m");
	EVENTHANDLER.add_event("5m");
}
int _prevTime = 0;
Time RunTime;

void setup() {
	//Enable WatchDog
	wdt_disable();
	delay(250);
	wdt_enable(WDTO_4S);
	delay(250);
	wdt_reset();//"Pat the Dog" Good Boy!

	Serial.begin(9600);
	
	Wire.begin();
	InitClock();
	
	static arduino_mega mainBoard;
}



void loop() {
	int currentTime = millis()/100;
	if (currentTime - _prevTime < 1) return;
	RunTime.Tenths++;
	EVENTHANDLER.trigger(".1s", &RunTime, 0);
	if (RunTime.Tenths % 5 == 0) EVENTHANDLER.trigger(".5s", &RunTime, 0);

	if(RunTime.Tenths == 10) {
		
		RunTime.Seconds++;
		RunTime.Tenths = 0;
		
		EVENTHANDLER.trigger("1s", &RunTime, 0);
		if (RunTime.Seconds % 5 == 0)	EVENTHANDLER.trigger("5s", &RunTime, 0);
		if (RunTime.Seconds % 10 == 0)	EVENTHANDLER.trigger("10s", &RunTime, 0);
		if (RunTime.Seconds % 15 == 0)	EVENTHANDLER.trigger("15s", &RunTime, 0);
		if (RunTime.Seconds % 30 == 0)	EVENTHANDLER.trigger("30s", &RunTime, 0);
		
		if (RunTime.Seconds == 60) {

			RunTime.Seconds = 0;
			RunTime.Minutes++;
			
			EVENTHANDLER.trigger("1m", &RunTime, 0);
			if (RunTime.Minutes % 5 == 0)  EVENTHANDLER.trigger("5m", &RunTime, 0);
			if (RunTime.Minutes % 15 == 0) EVENTHANDLER.trigger("15m", &RunTime, 0);
			if (RunTime.Minutes % 30 == 0) EVENTHANDLER.trigger("30m", &RunTime, 0);

			if (RunTime.Minutes == 60) {
				RunTime.Minutes = 0;
				RunTime.Hours++;
			}
		}
	}
	int loopExecutionTime = millis()/100 - currentTime;
	_prevTime = currentTime + loopExecutionTime;
	wdt_reset();
}
