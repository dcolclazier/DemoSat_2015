#pragma once
#include "WString.h"
#include "EventHandler.h"
#include <SD.h>
#include "sd_shield.h"

SIMPLEUNARYACTION(log_bno_update, SD_Shield* logger)

File _logfile;
SD_Shield* _logger;
String _filename;
};

SIMPLEUNARYACTION(log_alt_update, SD_Shield* logger)

File _logfile;
SD_Shield* _logger;
String _filename;
};
