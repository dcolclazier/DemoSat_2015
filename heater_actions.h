#pragma once

#include "EventHandler.h"

ACTION(update_heater_status) {
	ACTIONINIT(update_heater_status);
	int heater_control = 11;
};

//
//struct update_heater_status : public EventAction
//{
//	//update_heater_status(const HeaterController& ctrl) : _controller(ctrl) {}
//	update_heater_status() {
//		pinMode(HeaterControl, OUTPUT);
//		analogWrite(HeaterControl, 0);
//	}
//	void execute(EventArgs* args, void* trigger) override;
//private:
//	//HeaterController _controller;
//	int HeaterControl = 11;
//	
//};