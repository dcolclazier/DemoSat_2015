#pragma once
#include "Vector.h"

class Event {
public:
	void invoke(EventArgs* args, void* trigger);
	void add_action(EventAction* action);

private:
	int _actionCount;
	Vector<EventAction*> _actionList;
};
