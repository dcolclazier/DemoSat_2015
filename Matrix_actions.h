#pragma once
#include "EventHandler.h"
#include <Adafruit_LEDBackpack.h>

CREATE_ACTION_1ARG(update_config_status, Adafruit_BicolorMatrix bicolor)
Adafruit_BicolorMatrix _matrix;
END_CREATE


//CREATE_ACTION_1ARG()