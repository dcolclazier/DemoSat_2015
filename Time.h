#pragma once
#include "EventArgs.h"

struct Time : EventArgs {
	int Hours = 0;
	int Minutes = 0;
	int Seconds = 0;
	int Tenths = 0;
};
