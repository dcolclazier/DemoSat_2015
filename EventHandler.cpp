#include "EventHandler.h"
void EventHandler::add_event(const char* name, Event* eventToAdd) {
	if (_events.contains(name)) return;
	if (eventToAdd == 0) return;

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

void EventHandler::trigger(const char* name, EventArgs* args, void* trigger) {
	if (!contains(name)) return;
	_events.get(name)->invoke(args, trigger);
}