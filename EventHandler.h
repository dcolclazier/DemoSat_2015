#pragma once
#include "EventDictionary.h"
#include "EventAction.h"
#include "Event.h"
#include "EventArgs.h"
//class Event;
//class EventAction;
//class EventArgs;

class EventHandler {
public:
	static EventHandler& instance() {
		static EventHandler me;
		return me;
	}

	void add_event(const char* name);
	void add_eventAction(const char* name, EventAction* action);
	bool contains(const char* name);
	Event* get(const char* name);
	void trigger(const char* name, EventArgs* args, void* trigger);
	void trigger(const char* name, EventArgs* args);
	void trigger(const char* name);


private:
	EventHandler() {}
	EventHandler(EventHandler const&) = delete;
	void operator=(EventHandler const&) = delete;

	EventDictionary _events;

};

#define EVENTHANDLER\
	EventHandler::instance()
