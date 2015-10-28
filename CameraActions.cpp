#include "CameraActions.h"

SETUP_ACTION(take_picture) {
	
	pinMode(53, OUTPUT);
	if(!cam.begin()) {
		Serial.println("Camera not found...");
	}
	char* reply = cam.getVersion();
	if (reply == 0) Serial.println("Failed to get version.");
	else {
		Serial.println("--------------");
		Serial.println(reply);
		Serial.println("--------------");
	}
	cam.setImageSize(VC0706_640x480);
	uint8_t imgSize = cam.getImageSize();
	Serial.print("Image size: ");
	Serial.println(imgSize);
	EVENTHANDLER.add_event("save picture");

}
EXECUTE_ACTION(take_picture) {
	
	if (!cam.takePicture()) Serial.println("Failed to snap");
	else {
		Serial.println("Picture taken!");
		EVENTHANDLER.trigger("save picture", &cam);
	}
}

SETUP_ACTION_1ARG(save_picture, const SD_Shield& logger) : _logger(logger){ }

EXECUTE_ACTION(save_picture) {
	_cam = static_cast<Adafruit_VC0706*>(trigger);
	uint16_t jpglen = _cam->frameLength();
	Serial.print("Storing ");
	Serial.print(jpglen, DEC);
	Serial.print(" byte image.");

	Serial.println("Starting picture file check..");
	char filename[] = "IMAGE00.JPG";
	for (uint8_t i = 0; i < 100; i++) {
		filename[5] = '0' + i / 10;
		filename[6] = '0' + i % 10;
		// create if does not exist, do not open existing, write, sync after write
		if (!SD.exists(filename)) {
			_pictureFile = SD.open(filename, O_CREAT | O_WRITE);
			_filename = filename;
			Serial.println(_filename);
			break;
		}
	}	

	unsigned long time = millis();
	//pinMode(8,OUTPUT)
	_pictureFile = SD.open(_filename, O_CREAT | O_WRITE);
	byte writeCount = 0;
	while(jpglen > 0) {
		uint8_t bytesToRead = min(32, jpglen);
		uint8_t* buffer = _cam->readPicture(bytesToRead);
		_pictureFile.write(buffer, bytesToRead);
		if(++writeCount >= 64) {
			Serial.print(".");
			writeCount = 0;
		}
		jpglen -= bytesToRead;
	}
	_pictureFile.close();


	time = millis() - time;
	Serial.println("done!");
	Serial.print(time);
	Serial.println(" ms elapsed");
}