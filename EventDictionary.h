#pragma once
#include "WString.h"
#include "Vector.h"


class Event;

class EventDictionary {
public:
	void add_event(const String& name, Event* eventToAdd);
	Event* get(const String& name);
	bool contains(const String& name) const;

private:
	struct EventKeyValue {
		String key;
		Event* value;
	};

	Vector<EventKeyValue*> _eventList;
	
};
