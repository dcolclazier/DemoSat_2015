#pragma once
#include <Arduino.h>
#include "SD.h"
class DateTime;
class arduino_mega;
class SD_Shield {
public:

	explicit SD_Shield(arduino_mega* redboard);
	DateTime getTime() const;

private:
	arduino_mega* _mfc;
	const byte chipSelect = 4;
	Sd2Card _card;
	SdVolume _volume;
	SdFile _root;
		
};



