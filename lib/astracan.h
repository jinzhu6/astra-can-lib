/**
 * @brief HardwareCAN definitions
 */

#ifndef _ASTRA_CAN_H_
#define _ASTRA_CAN_H_

#include "utility/can.h"
#include "usb_serial.h"

enum ASTRA_CAN_BUS {
	LS,		/* LS or SW bus */
	MS,		
	HS
};

typedef enum ROLE {
	PRIMARY,
	SECONDARY
} ROLE;

// flags //
bool flagLightsOff;
bool flagMove;


class AstraCAN
{
private:
public:
	CAN_Port* Port;
	ASTRA_CAN_BUS bus;
	ROLE role;
	CAN_GPIO_MAP remap;
	/**
	* remap = пины (b8b9 или a11a12)
	* шина = LS / MS / HS
	* роль = основной / вторичный 
	*/
	AstraCAN(CAN_GPIO_MAP remap, ASTRA_CAN_BUS bus, ROLE role);  
    /** 
     * сразу установить до 14 фильтров
     */
    AstraCAN(CAN_GPIO_MAP remap, ASTRA_CAN_BUS bus, ROLE role, uint32 filters[]);
    AstraCAN(void);
    
    CAN_STATUS begin(void);
    CAN_STATUS begin(CAN_SPEED speed, uint32 mode);

	uint32 MSR(void)
	{
		return Port->MSR;
	}

	uint32 RF0R(void)
	{
		return Port->RF0R;
	}

	void set_pool_mode(void);
	void set_irq_mode(void);

	void end(void);

	CAN_STATUS filter(uint8 idx, uint32 id, uint32 mask);
	CAN_STATUS map(CAN_GPIO_MAP remap);
	CAN_STATUS status(void);

	CAN_TX_MBX send(CanMsg* message);
	CAN_TX_MBX sendMessage(long id=0x001, byte dlength=8, byte d0=0x00, byte d1=0x00, byte d2=0x00, byte d3=0x00, byte d4=0x00, byte d5=0x00, byte d6=0x00, byte d7=0x00);
	
	void cancel(CAN_TX_MBX mbx);

	uint8 available(void);

	CanMsg* recv(void);
	CanMsg* recv(uint32 id);

	void free(void);
	void clear(void);

	uint8 fifo_ready(CAN_FIFO fifo);
	CanMsg* read(CAN_FIFO fifo, CanMsg* msg);
	void release(CAN_FIFO fifo);

	// MS CAN only:
	void volumeDown(void);
};

#endif