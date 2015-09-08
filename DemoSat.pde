#include "EventHandler.h"
#include "Event.h"
#include "RedBoard.h"
#include "Time.h"
#include <Arduino.h>

void InitClock() {
	EventHandler::instance().add_event(".1s", new Event);
	EventHandler::instance().add_event("1s", new Event);
	EventHandler::instance().add_event("5s", new Event);
	EventHandler::instance().add_event("15s", new Event);
	EventHandler::instance().add_event("30s", new Event);
	EventHandler::instance().add_event("1m", new Event);
	EventHandler::instance().add_event("5m", new Event);
}
int _prevTime = 0;
int _tickTimeInmillis = 500;
Time RunTime;

void setup() {
	InitClock();
	RedBoard mainBoard;
}



void loop() {
	int currentTime = millis()/100;
	if (currentTime - _prevTime < 1) return;
	RunTime.Tenths++;
	EventHandler::instance().trigger(".1s", 0, 0);
	if(RunTime.Tenths == 10) {
		
		RunTime.Seconds++;
		RunTime.Tenths = 0;
		
		EventHandler::instance().trigger("1s", 0, 0);
		if (RunTime.Seconds % 5 == 0)	EventHandler::instance().trigger("5s", 0, 0);
		if (RunTime.Seconds % 15 == 0)	EventHandler::instance().trigger("15s", 0, 0);
		if (RunTime.Seconds % 30 == 0)	EventHandler::instance().trigger("30s", 0, 0);
		
		if (RunTime.Seconds == 60) {

			RunTime.Seconds = 0;
			RunTime.Minutes++;
			
			EventHandler::instance().trigger("1m", 0, 0);
			if (RunTime.Minutes % 5 == 0)EventHandler::instance().trigger("5m", 0, 0);

			if (RunTime.Minutes == 60) {
				RunTime.Minutes = 0;
				RunTime.Hours++;
			}
		}
	}
	int loopExecutionTime = millis()/100 - currentTime;
	_prevTime = currentTime + loopExecutionTime;
}
