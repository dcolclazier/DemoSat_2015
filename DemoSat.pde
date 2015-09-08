#include "EventHandler.h"
#include "Event.h"
#include "RedBoard.h"
#include "Time.h"

void InitClock() {
	EventHandler::instance().add_event("1s", new Event);
	EventHandler::instance().add_event("5s", new Event);
	EventHandler::instance().add_event("15s", new Event);
	EventHandler::instance().add_event("30s", new Event);
	EventHandler::instance().add_event("1m", new Event);
	EventHandler::instance().add_event("5m", new Event);
}
int _prevTime = 0;
int _tickTime = 1000;
Time RunTime;

void setup() {
	InitClock();
	RedBoard mainBoard;
}



void loop() {
	int currentTime = millis();
	if (currentTime - _prevTime < _tickTime) return;


	RunTime.Seconds++;
	EventHandler::instance().trigger("1s", 0, 0);

	if (RunTime.Seconds == 60) {
		EventHandler::instance().trigger("1m", 0, 0);

		if (RunTime.Minutes == 59) {
			RunTime.Hours++;
			RunTime.Minutes = 0;
		}
		else {
			RunTime.Minutes++;
		}
		RunTime.Seconds = 0;
	}
	if (RunTime.Seconds % 5 == 0)EventHandler::instance().trigger("5s", 0, 0);
	if (RunTime.Seconds % 15 == 0)EventHandler::instance().trigger("15s", 0, 0);
	if (RunTime.Seconds % 30 == 0)EventHandler::instance().trigger("30s", 0, 0);
	if (RunTime.Minutes % 5 == 0)EventHandler::instance().trigger("5m", 0, 0);
	int loopExecutionTime = millis() - currentTime;
	_prevTime = currentTime + loopExecutionTime;
}
