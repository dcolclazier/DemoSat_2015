#pragma once
class EventArgs;
class EventAction {
public:
	virtual ~EventAction() {}
	virtual void execute(EventArgs* args, void* trigger) = 0;
};
#define CREATE_ACTION(name, out_argtype)\
	struct name : public EventAction {\
	ACTIONINIT(name, out_argtype);

#define INIT_ACTION(name, argtype)\
	name();\
	void execute(EventArgs* args, void* trigger) override;\
private:\
	argtype _args\

#define CREATE_SIMPLEACTION(name)\
	struct name : public EventAction {\
	SIMPLEACTIONINIT(name);

#define SIMPLEACTIONSETUP(action)\
	action::action()

#define SIMPLEACTIONINIT(name)\
	name();\
	void execute(EventArgs* args, void* trigger) override;\
	private:\

#define SIMPLEUNARYACTION(name, arg1)\
	struct name : public EventAction {\
	SIMPLEUNARYACTIONINIT(name, arg1);

#define SIMPLEUNARYACTIONSETUP(name)\
	name::name()

#define SIMPLEUNARYACTIONINIT(name, arg1)\
	name(arg1);\
	void execute(EventArgs* args, void* trigger) override;\
	private:\

#define SIMPLEBINARYACTION(name, arg1, arg2)\
	struct name : public EventAction {\
	SIMPLEBINARYACTIONINIT(name, arg1, arg2);

#define SIMPLEBINARYACTIONSETUP(name, arg1, arg2)\
	name::name(arg1, arg2)

#define SIMPLEBINARYACTIONINIT(name, arg1, arg2)\
	name(arg1, arg2);\
	void execute(EventArgs* args, void* trigger) override;\
private:\


#define UNARYACTION(name, out_argtype, in_arg1)\
	struct name : public EventAction {\
	UNARYACTIONINIT(name, out_argtype, in_arg1);\

#define UNARYACTIONINIT(name, argtype, arg1)\
	name(arg1);\
	void execute(EventArgs* args, void* trigger) override;\
private:\
	argtype _args\

#define UNARYACTIONSETUP(action,arg1)\
	action::action(arg1)


#define BINARYACTION(name, out_argtype, in_arg1, in_arg2)\
	struct name : public EventAction {\
	BINARYACTIONINIT(name, out_argtype, in_arg1, in_arg2);

#define BINARYACTIONINIT(name, argtype, arg1, arg2)\
	name(arg1, arg2);\
	void execute(EventArgs* args, void* trigger) override;\
private:\
	argtype _args\

#define BINARYACTIONSETUP(action,arg1, arg2)\
	action::action(arg1, arg2)

#define ACTIONCLEANUP(action)\
	void action::~action()

#define ACTIONEXECUTE(action)\
	void action::execute(EventArgs* args, void* trigger)