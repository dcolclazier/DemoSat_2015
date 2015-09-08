#pragma once



class EventArgs;
class EventAction {
public:
	virtual ~EventAction() {}

	virtual void execute(EventArgs* args, void* trigger) = 0;
};

#define ACTION(name)\
	struct name : public EventAction

#define EXECUTE\
	void execute(EventArgs* args, void* trigger) override
