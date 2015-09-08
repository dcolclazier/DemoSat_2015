#pragma once
#include "WString.h"
#include "EventDictionary.h"
class Event;
class EventAction;
class EventArgs;

class EventHandler {
public:
	static EventHandler& instance() {
		static EventHandler me;
		return me;
	}

	void add_event(const String& name, Event* eventToAdd);
	void add_eventAction(const String& name, EventAction* action);
	bool contains(const String& name);
	Event* get(const String& name);
	void trigger(const String& name, EventArgs* args, void* trigger);



private:
	EventHandler() {}
	EventHandler(EventHandler const&) = delete;
	void operator=(EventHandler const&) = delete;

	EventDictionary _events;

};


