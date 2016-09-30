#include "RTClib.h"
#include "arduino_mega.h"
#include <avr/pgmspace.h>
#include "sd_shield.h"

SD_Shield::SD_Shield(arduino_mega* mfc) : _mfc(mfc){
	pinMode(SS, OUTPUT);
	while (!_card.init(SPI_HALF_SPEED, 10)) {
		Serial.println(("Something went wrong with the SD Card init..."));
	}
	if (!_volume.init(_card)) {
		Serial.println(("Couldn't find FAT16/FAT32 partition..."));
		return;
	}
	SD.begin(10);

}

DateTime SD_Shield::getTime() const {
	return _mfc->getTime();
}

