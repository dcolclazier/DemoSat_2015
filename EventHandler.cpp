#include "EventHandler.h"
#include "Event.h"
void EventHandler::add_event(const String& name, Event* eventToAdd) {
	if (_events.contains(name)) return;
	if (eventToAdd == 0) return;

	_events.add_event(name, eventToAdd);
}

void EventHandler::add_eventAction(const String& name, EventAction* action) {
	if (!contains(name)) return;
	_events.get(name)->add_action(action);
}

bool EventHandler::contains(const String& name) {
	return _events.contains(name);
}

Event* EventHandler::get(const String& name) {
	if (!contains(name)) return 0;
	return _events.get(name);
}

void EventHandler::trigger(const String& name, EventArgs* args, void* trigger) {
	if (!contains(name)) return;
	_events.get(name)->invoke(args, trigger);
}