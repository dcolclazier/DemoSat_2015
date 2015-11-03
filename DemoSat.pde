#include "UV_Sensor.h"
#include "Matrix_actions.h"
#include "Matrix_actions.h"
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_SI1145.h>
#include <Adafruit_VC0706.h>
#include <Adafruit_MotorShield.h>
#include "EventHandler.h"
#include "EventData.h"
#include "Event.h"
#include "arduino_mega.h"
#include <avr/pgmspace.h>
#include <avr/wdt.h>//For WatchDog
#include <Arduino.h>

#include "Wire.h"
#include <Adafruit_SI1145.h>
#include <SoftwareSerial.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include <HIH6130.h>
#include <Adafruit_BMP085_U.h>
#include <SPI.h>
#include <RTClib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SD.h>
#include "sd_shield.h"


void InitClock() {

	EVENTHANDLER.add_event(".1s");
	EVENTHANDLER.add_event(".2s");
	EVENTHANDLER.add_event(".5s");
	EVENTHANDLER.add_event("1s");
	EVENTHANDLER.add_event("2s");
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
	wdt_enable(WDTO_4S);//Timer for 4000 Milliseconds
	delay(250);
	wdt_reset();//"Pat the Dog" Good Boy!
	Serial.begin(9600);
	
	Wire.begin();

	OneWire oneWireBus(2);
	
	InitClock();
	
	static arduino_mega mainBoard;
}


void loop() {
	int currentTime = millis()/100;
	if (currentTime - _prevTime < 1) return;
	RunTime.Tenths++;

	EVENTHANDLER.trigger(".1s");
	if (RunTime.Tenths % 2 == 0) EVENTHANDLER.trigger(".2s");
	if (RunTime.Tenths % 5 == 0) EVENTHANDLER.trigger(".5s");

	if(RunTime.Tenths == 10) {
		
		RunTime.Seconds++;
		RunTime.Tenths = 0;
		
		EVENTHANDLER.trigger("1s");
		if (RunTime.Seconds % 2 == 0)	EVENTHANDLER.trigger("2s");
		if (RunTime.Seconds % 5 == 0)	EVENTHANDLER.trigger("5s");
			
		if (RunTime.Seconds == 60) {

			RunTime.Seconds = 0;
			RunTime.Minutes++;
	
			if (RunTime.Minutes == 60) {
				RunTime.Minutes = 0;
				RunTime.Hours++;
			}
		}
	}
	int loopExecutionTime = millis()/100 - currentTime;
	Serial.print("loop execution time: ");
	Serial.println(loopExecutionTime);
	_prevTime = currentTime + loopExecutionTime;

	wdt_reset();//pat the dog "good boy!"
}
