

#include "EventHandler.h"
#include "EventArgs.h"
#include "Event.h"
#include "arduino_mega.h"

#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include <Adafruit_BMP085_U.h>
#include <SPI.h>
#include <RTClib.h>
#include <SD.h>
#include "sd_shield.h"


void InitClock() {

	//Test

	EVENTHANDLER.add_event(".1s", new Event);
	EVENTHANDLER.add_event(".5s", new Event);
	EVENTHANDLER.add_event("1s", new Event);
	EVENTHANDLER.add_event("5s", new Event);
	EVENTHANDLER.add_event("15s", new Event);
	EVENTHANDLER.add_event("30s", new Event);
	EVENTHANDLER.add_event("1m", new Event);
	EVENTHANDLER.add_event("5m", new Event);
}
int _prevTime = 0;
Time RunTime;

void setup() {
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
}
