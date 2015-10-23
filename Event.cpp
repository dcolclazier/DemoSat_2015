#include "EventData.h"
#include "EventAction.h"
#include "Event.h"

void Event::invoke(EventData* args, void* trigger) {
	for (int i = 0; i < _actionList.size(); i++) {
		EventAction* action = _actionList[i];
		action->execute(args, trigger);
	}
}
void Event::add_action(EventAction* action) {
	if (_actionList.contains(action)) return;
	_actionList.push_back(action);
}
void Event::remove_action(EventAction* event_action) {
	if (!_actionList.contains(event_action)) return;
	_actionList.remove(event_action);
}