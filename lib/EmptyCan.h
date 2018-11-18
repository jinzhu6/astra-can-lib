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
	
	void sendMessage(long id, byte dlength, byte d0, byte d1, byte d2, byte d3, byte d4, byte d5, byte d6, byte d7);
	
};

#endif
