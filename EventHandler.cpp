#include "EventHandler.h"
void EventHandler::add_event(const char* name) {
	if (_events.contains(name)) return;
	//if (eventToAdd == 0) return;
	Event * eventToAdd = new Event;
	_events.add_event(name, eventToAdd);
}

void EventHandler::add_eventAction(const char* name, EventAction* action) {
	if (!contains(name)) return;
	_events.get(name)->add_action(action);
}

bool EventHandler::contains(const char* name) {
	return _events.contains(name);
}

Event* EventHandler::get(const char* name) {
	if (!contains(name)) return 0;
	return _events.get(name);
}

void EventHandler::trigger(const char* name, EventData* args, void* trigger) {
	if (!contains(name)) return;
	_events.get(name)->invoke(args, trigger);
}
void EventHandler::trigger(const char* name, EventData* args) {
	if (!contains(name)) return;
	_events.get(name)->invoke(args, 0);
}
void EventHandler::trigger(const char* name) {
	if (!contains(name)) return;
	_events.get(name)->invoke(0, 0);
}