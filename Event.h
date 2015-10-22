﻿#pragma once
#include "Vector.h"

class EventAction;
class EventData;

class Event {
public:
	void invoke(EventData* args, void* trigger);
	void add_action(EventAction* action);
	void remove_action(EventAction* event_action);
private:
	int _actionCount;
	Vector<EventAction*> _actionList;
};
