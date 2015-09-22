#pragma once
#include "Vector.h"


class Event;

class EventDictionary {
public:
	void add_event(const char* name, Event* eventToAdd);
	Event* get(const char* name);
	bool contains(const char* name) const;

private:
	struct EventKeyValue {
		const char* key;
		Event* value;
	};

	Vector<EventKeyValue*> _eventList;
	
};
