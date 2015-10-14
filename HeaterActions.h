#pragma once

#include "EventAction.h"
#include "HeaterController.h"


struct check_temperature : public EventAction
{
	//check_temperature(const HeaterController& ctrl) : _controller(ctrl) {}
	check_temperature();
	void execute(EventArgs* args, void* trigger) override;
private:
	//HeaterController _controller;
};