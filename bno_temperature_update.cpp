#include "bno_temperature_update.h"
#include "EventArgs.h"
#include "EventAction.h"
#include "EventHandler.h"
#include "Event.h"

UNARYACTIONSETUP(bno_temperature_update, Adafruit_BNO055 bno) {
	_bno = bno;
	EVENTHANDLER.add_event("bno_tmp_upd", new Event);
} 
ACTIONEXECUTE(bno_temperature_update) {
	
	//_temp.Temp = _bno.getTemp();
	//EVENTHANDLER.trigger("bno_tmp_upd", &_temp, &_bno);
}