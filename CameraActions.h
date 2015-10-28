#pragma once
#include "EventAction.h"
#include <Adafruit_VC0706.h>
#include "sd_shield.h"
#include <SoftwareSerial.h>

CREATE_ACTION(take_picture)

	SoftwareSerial cameraConnection = SoftwareSerial(62, 53); // tx, rx
	Adafruit_VC0706 cam = Adafruit_VC0706(&cameraConnection);

END_CREATE

struct save_picture : public EventAction { 
	save_picture(const SD_Shield& logger); 
	void execute(EventData* args, void* trigger) override; 
private: ; 
	const SD_Shield _logger;
	char* _filename;
	Adafruit_VC0706* _cam;
	File _pictureFile;
	END_CREATE

//CREATE
