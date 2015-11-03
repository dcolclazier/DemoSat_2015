#pragma once

#define MOTORSHIELD_INIT_ALTITUDE 500
#define DOOR1_OPEN_ALT 600
#define DOOR1_CLOSE_ALT 900
#define DOOR2_OPEN_ALT 1800
#define DOOR2_CLOSE_ALT 2000
#define MOTOR_FAST 50
#define MOTOR_SLOW 200	


class EventData;
class EventAction {
public:
	virtual ~EventAction() {}
	virtual void execute(EventData* args, void* trigger) = 0;
};
#define CREATE_EVENT_TRIGGERING_ACTION(name, out_argtype)\
	struct name : public EventAction {\
	INIT_ACTION(name, out_argtype);

#define INIT_ACTION(name, argtype)\
	name();\
	void execute(EventData* args, void* trigger) override;\
private:\
	argtype _args\

#define CREATE_ACTION(name)\
	struct name : public EventAction {\
	SIMPLEACTIONINIT(name);

#define SETUP_ACTION(action)\
	action::action()

#define SIMPLEACTIONINIT(name)\
	name();\
	void execute(EventData* args, void* trigger) override;\
	private:\

#define CREATE_ACTION_1ARG(name, arg1)\
	struct name : public EventAction {\
	SIMPLEUNARYACTIONINIT(name, arg1);

#define SETUP_ACTION_1ARG(name, arg1)\
	name::name(arg1)

#define SIMPLEUNARYACTIONINIT(name, arg1)\
	name(arg1);\
	void execute(EventData* args, void* trigger) override;\
	private:\

#define CREATE_ACTION_TWO_ARGS(name, arg1, arg2)\
	struct name : public EventAction {\
	SIMPLEBINARYACTIONINIT(name, arg1, arg2);

#define SETUP_ACTION_2ARGS(name, arg1, arg2)\
	name::name(arg1, arg2)

#define SIMPLEBINARYACTIONINIT(name, arg1, arg2)\
	name(arg1, arg2);\
	void execute(EventData* args, void* trigger) override;\
private:\

#define CREATE_ACTION_3ARGS(name,arg1,arg2,arg3)\
	struct name : public EventAction {\
	SIMPLETERENARYACTIONINIT(name, arg1, arg2, arg3)\

#define SIMPLETERENARYACTIONINIT(name,arg1,arg2,arg3)\
	name(arg1,arg2,arg3);\
	void execute(EventData* args, void* trigger) override;\
private:\

#define SETUP_ACTION_3ARGS(name, arg1, arg2, arg3)\
	name::name(arg1,arg2,arg3)

#define SETUP_ACTION_4ARGS(name, arg1, arg2, arg3, arg4)\
	name::name(arg1,arg2,arg3,arg4)

#define SETUP_ACTION_5ARGS(name, arg1, arg2, arg3, arg4)\
	name::name(arg1,arg2,arg3,arg4,arg5)


#define CREATE_EVENT_TRIGGERING_ACTION_1ARG(name, out_argtype, in_arg1)\
	struct name : public EventAction {\
	UNARYACTIONINIT(name, out_argtype, in_arg1);\

#define UNARYACTIONINIT(name, argtype, arg1)\
	name(arg1);\
	void execute(EventData* args, void* trigger) override;\
private:\
	argtype _args\

//#define SETUP_TRIGGERACTION_ONE_ARG(action,arg1)\
//	action::action(arg1)


#define CREATE_EVENT_TRIGGERING_ACTION_2ARGS(name, out_argtype, in_arg1, in_arg2)\
	struct name : public EventAction {\
	BINARYACTIONINIT(name, out_argtype, in_arg1, in_arg2);

#define BINARYACTIONINIT(name, argtype, arg1, arg2)\
	name(arg1, arg2);\
	void execute(EventData* args, void* trigger) override;\
private:\
	argtype _args\

#define CREATE_EVENT_TRIGGERING_ACTION_3ARGS(name, out_argtype, in_arg1, in_arg2, in_arg3)\
	struct name : public EventAction {\
	TERENARYACTIONINIT(name, out_argtype, in_arg1, in_arg2, in_arg3);

#define TERENARYACTIONINIT(name, argtype, arg1, arg2, arg3)\
	name(arg1, arg2, arg3);\
	void execute(EventData* args, void* trigger) override;\
private:\
	argtype _args\

#define CREATE_EVENT_TRIGGERING_ACTION_4ARGS(name, out_argtype, in_arg1, in_arg2, in_arg3, in_arg4)\
	struct name : public EventAction {\
	QUADACTIONINIT(name, out_argtype, in_arg1, in_arg2, in_arg3, in_arg4);

#define QUADACTIONINIT(name, argtype, arg1, arg2, arg3, arg4)\
	name(arg1, arg2, arg3, arg4);\
	void execute(EventData* args, void* trigger) override;\
private:\
	argtype _args\

#define CREATE_EVENT_TRIGGERING_ACTION_5ARGS(name, out_argtype, in_arg1, in_arg2, in_arg3, in_arg4, in_arg5)\
	struct name : public EventAction {\
	QUINTENARYACTIONINIT(name, out_argtype, in_arg1, in_arg2, in_arg3, in_arg4, in_arg5);

#define QUINTENARYACTIONINIT(name, argtype, arg1, arg2, arg3, arg4, arg5)\
	name(arg1, arg2, arg3, arg4, arg5);\
	void execute(EventData* args, void* trigger) override;\
private:\
	argtype _args\

//#define SETUP_TRIGGERACTION_TWO_ARGS(action,arg1, arg2)\
//	action::action(arg1, arg2)

#define CLEANUP_ACTION(action)\
	void action::~action()

#define EXECUTE_ACTION(action)\
	void action::execute(EventData* args, void* trigger)

#define END_CREATE };