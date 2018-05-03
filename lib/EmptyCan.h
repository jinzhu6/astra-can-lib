#ifndef _EmptyCan_
#define _EmptyCan_

#include "utility/can.h"
#include "usb_serial.h"
#include <HardwareCAN.h>

class EmptyCan:HardwareCAN {
	private:
	
	public:
	
	
	EmptyCan(void);
	
	void begin(void);
	
	
}