#pragma once
class EventArgs;
class EventAction {
public:
	virtual ~EventAction() {}

	virtual void execute(EventArgs* args, void* trigger) = 0;
};

#define ACTION(name)\
	struct name : public EventAction\
		

#define ACTIONEXECUTE(action)\
	void action::execute(EventArgs* args, void* trigger)

#define ACTIONINIT(name)\
	name();\
	void execute(EventArgs* args, void* trigger) override

#define UNARYACTIONINIT(name, arg1)\
	name(arg1);\
	void execute(EventArgs* args, void* trigger) override

#define ACTIONINIT(name)\
	name();\
	void execute(EventArgs* args, void* trigger) override

#define ACTIONSETUP(action)\
	action::action()

#define UNARYACTIONSETUP(action,arg1)\
	action::action(arg1)

#define BINARYACTIONSETUP(action,arg1, arg2)\
	action::action(arg1, arg2)