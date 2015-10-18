#pragma once
class EventArgs;
class EventAction {
public:
	virtual ~EventAction() {}
	virtual void execute(EventArgs* args, void* trigger) = 0;
};
#define CREATE_EVENT_TRIGGERING_ACTION(name, out_argtype)\
	struct name : public EventAction {\
	ACTIONINIT(name, out_argtype);

#define INIT_ACTION(name, argtype)\
	name();\
	void execute(EventArgs* args, void* trigger) override;\
private:\
	argtype _args\

#define CREATE_ACTION(name)\
	struct name : public EventAction {\
	SIMPLEACTIONINIT(name);

#define SETUP_ACTION(action)\
	action::action()

#define SIMPLEACTIONINIT(name)\
	name();\
	void execute(EventArgs* args, void* trigger) override;\
	private:\

#define CREATE_ACTION_ONE_ARG(name, arg1)\
	struct name : public EventAction {\
	SIMPLEUNARYACTIONINIT(name, arg1);

#define SETUP_ACTION_ONE_ARG(name, arg1)\
	name::name(arg1)

#define SIMPLEUNARYACTIONINIT(name, arg1)\
	name(arg1);\
	void execute(EventArgs* args, void* trigger) override;\
	private:\

#define CREATE_ACTION_TWO_ARGS(name, arg1, arg2)\
	struct name : public EventAction {\
	SIMPLEBINARYACTIONINIT(name, arg1, arg2);

#define SETUP_ACTION_TWO_ARGS(name, arg1, arg2)\
	name::name(arg1, arg2)

#define SIMPLEBINARYACTIONINIT(name, arg1, arg2)\
	name(arg1, arg2);\
	void execute(EventArgs* args, void* trigger) override;\
private:\


#define CREATE_EVENT_TRIGGERING_ACTION_1ARG(name, out_argtype, in_arg1)\
	struct name : public EventAction {\
	UNARYACTIONINIT(name, out_argtype, in_arg1);\

#define UNARYACTIONINIT(name, argtype, arg1)\
	name(arg1);\
	void execute(EventArgs* args, void* trigger) override;\
private:\
	argtype _args\

//#define SETUP_TRIGGERACTION_ONE_ARG(action,arg1)\
//	action::action(arg1)


#define CREATE_EVENT_TRIGGERING_ACTION_2ARGS(name, out_argtype, in_arg1, in_arg2)\
	struct name : public EventAction {\
	BINARYACTIONINIT(name, out_argtype, in_arg1, in_arg2);

#define BINARYACTIONINIT(name, argtype, arg1, arg2)\
	name(arg1, arg2);\
	void execute(EventArgs* args, void* trigger) override;\
private:\
	argtype _args\

//#define SETUP_TRIGGERACTION_TWO_ARGS(action,arg1, arg2)\
//	action::action(arg1, arg2)

#define CLEANUP_ACTION(action)\
	void action::~action()

#define EXECUTE_ACTION(action)\
	void action::execute(EventArgs* args, void* trigger)

#define END_CREATE };