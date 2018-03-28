/**
 * @brief HardwareCAN definitions
 */

#ifndef _ASTRA_CAN_H_
#define _ASTRA_CAN_H_

#include "utility/can.h"
#include "usb_serial.h"


class AstraCAN
{
private:
public:
	CAN_Port* Port;
	/**
	* порт = пины
	* шина = ls / ms / hs
	* роль = основной / вторичный 
	*/
    AstraCAN(CAN_Port *CANx_BASE, Astra_Bus bus, Device_Role role);
    
    CAN_STATUS begin(void);

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

    CAN_STATUS begin(CAN_SPEED speed, uint32 mode);
	void end(void);

	CAN_STATUS filter(uint8 idx, uint32 id, uint32 mask);
	CAN_STATUS map(CAN_GPIO_MAP remap);
	CAN_STATUS status(void);

	CAN_TX_MBX send(CanMsg* message);
	void cancel(CAN_TX_MBX mbx);

	uint8 available(void);

	CanMsg* recv(void);

	void free(void);
	void clear(void);

	uint8 fifo_ready(CAN_FIFO fifo);
	CanMsg* read(CAN_FIFO fifo, CanMsg* msg);
	void release(CAN_FIFO fifo);
};

#endif