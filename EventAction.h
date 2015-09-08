#pragma once



class EventArgs;
class EventAction {
public:
	virtual ~EventAction() {}

	virtual void execute(EventArgs* args, void* trigger) = 0;
};

#define ACTION(name)\
	struct name : public EventAction

#define CLASSACTION(cls,nested,name)\
	struct cls::nested::name : public EventAction

#define EXECUTE\
	void execute(EventArgs* args, void* trigger) override
