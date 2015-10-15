#pragma once
#include <Arduino.h>

#include "EventHandler.h"
//#include "HeaterController.h"


struct check_temperature : public EventAction
{
	//check_temperature(const HeaterController& ctrl) : _controller(ctrl) {}
	check_temperature() {
		pinMode(HeaterControl, OUTPUT);
		analogWrite(HeaterControl, 0);
	}
	void execute(EventArgs* args, void* trigger) override;
private:
	//HeaterController _controller;
	int HeaterControl = 11;
	
};