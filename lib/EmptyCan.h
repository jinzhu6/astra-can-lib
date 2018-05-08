#ifndef _EmptyCan_
#define _EmptyCan_

#include "utility/can.h"
#include "usb_serial.h"
#include <HardwareCAN.h>

class EmptyCan : public HardwareCAN {
	private:
	public:
	

	EmptyCan(void):HardwareCAN(CAN1_BASE){
		

	}
	
};

#endif
