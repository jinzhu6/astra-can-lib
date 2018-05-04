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
	
	void sendMessage(0x5e8,4,0x81, d0, d1, d2,0,0,0,0);
	
	
}