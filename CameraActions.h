#pragma once
#include "EventAction.h"
#include <Adafruit_VC0706.h>
#include "sd_shield.h"
#include <SoftwareSerial.h>

CREATE_ACTION(take_picture)

	SoftwareSerial cameraConnection = SoftwareSerial(2, 3); // tx, rx
	Adafruit_VC0706 cam = Adafruit_VC0706(&cameraConnection);

END_CREATE

CREATE_ACTION_1ARG(save_picture, const SD_Shield* logger) 
	const SD_Shield* _logger;
	char* _filename;
	Adafruit_VC0706* _cam;
END_CREATE

//CREATE
