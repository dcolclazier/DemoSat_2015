#pragma once



class EventArgs;
class EventAction {
public:
	virtual ~EventAction() {}

	virtual void execute(EventArgs* args, void* trigger) = 0;
};

#define ACTION(name)\
	struct name : public EventAction

#define ACTIONEXECUTE(cls,action)\
	void cls::action::execute(EventArgs* args, void* trigger)

#define EXECUTE(name)\
	name();\
	void execute(EventArgs* args, void* trigger) override

#define ACTIONSETUP(cls,action)\
	cls::action::action()