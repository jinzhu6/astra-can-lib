/**
 * @brief AstraCAN "wiring-like" api for CAN
 */

#include "wirish.h"
#include "utility/can.h"
#include "AstraCAN.h"

/**
 * @brief Initialize a CAN peripheral
 * @param freq frequency to run at, must one of the following values:
 *           - CAN_SPEED_1000
 *           - CAN_SPEED_500
 *           - CAN_SPEED_250
 *           - CAN_SPEED_125
 *           - CAN_SPEED_95
 *           - CAN_SPEED_33
 */
CAN_STATUS AstraCAN::begin(CAN_SPEED speed, uint32 mode)
{
/*  Begin Fix JMD
	if (can_init(Port, CAN_MCR_NART, CAN_SPEED_250) == CAN_OK)	
		// NART empêche la réémission en cas de perte d'arbitrage d'où trames perdues
 */
	Serial.end();						// disable USB interface -- JMD
	if (can_init(Port, 0, speed) == CAN_OK)
 // End Fix JMD
		return can_set_mode(Port, mode);
	return can_status();
}

void AstraCAN::set_pool_mode(void)
{
	return can_set_pool_mode(Port);
}

void AstraCAN::set_irq_mode(void)
{
	return can_set_irq_mode(Port);
}

CAN_STATUS AstraCAN::filter(uint8 idx, uint32 id, uint32 mask)
{
	return can_filter(Port, idx, CAN_FIFO0, CAN_FILTER_32BIT, CAN_FILTER_MASK, id, mask);
}

CAN_STATUS AstraCAN::status(void)
{
	return can_status();
}

CAN_TX_MBX AstraCAN::send(CanMsg* message)
{
	return can_transmit(Port, message);
}
/**
 * формирование произвольного сообщения и отправка
 */
void AstraCAN::sendMessage(long id=0x001, byte dlength=8, byte d0=0x00, byte d1=0x00, byte d2=0x00, byte d3=0x00, byte d4=0x00, byte d5=0x00, byte d6=0x00, byte d7=0x00)
{
  // Initialize the message structure
  // A CAN structure includes the following fields:
  msg.IDE = CAN_ID_STD;          // Indicates a standard identifier ; CAN_ID_EXT would mean this frame uses an extended identifier
  msg.RTR = CAN_RTR_DATA;        // Indicated this is a data frame, as opposed to a remote frame (would then be CAN_RTR_REMOTE)
  msg.ID = id ;                  // Identifier of the frame : 0-2047 (0-0x3ff) for standard idenfiers; 0-0x1fffffff for extended identifiers
  msg.DLC = dlength;                   // Number of data bytes to follow

  // Prepare frame : send something
  msg.Data[0] = d0 ;
  msg.Data[1] = d1 ;
  msg.Data[2] = d2 ;
  msg.Data[3] = d3 ;
  msg.Data[4] = d4 ;
  msg.Data[5] = d5 ;
  msg.Data[6] = d6 ;
  msg.Data[7] = d7 ;

  digitalWrite(PC13, LOW);    // turn the onboard LED on
  CANsend(&msg) ;      // Send this frame            
  digitalWrite(PC13, HIGH);   // turn the LED off 
}


uint8 AstraCAN::available(void)
{
	return can_rx_available();
}

CanMsg* AstraCAN::recv(void)
{
	return can_rx_queue_get();
}

CanMsg* AstraCAN::recv(uint32 id)
{
	// todo! установить фильтр по id, получить сообщение, вернуть фильтры?
	return can_rx_queue_get();
}

void AstraCAN::clear(void)
{
	can_rx_queue_clear();
}

void AstraCAN::free(void)
{
	can_rx_queue_free();
}

void AstraCAN::cancel(CAN_TX_MBX mbx)
{
	can_cancel(Port, mbx);
}

/**
 * @brief Initialize a CAN peripheral
 */
CAN_STATUS AstraCAN::begin(void)
{
	// внимание!!!! это лс кан по умолчанию!
	return begin(CAN_SPEED_33, CAN_MODE_NORMAL);
}

void AstraCAN::end(void)
{
	can_deinit(Port);
}

CanMsg* AstraCAN::read(CAN_FIFO fifo, CanMsg* msg)
{
	return can_read(Port, fifo, msg);
}

void AstraCAN::release(CAN_FIFO fifo)
{
	can_rx_release(Port, fifo);
}

/**
 * @brief Initialize a CAN peripheral
 */
CAN_STATUS AstraCAN::map(CAN_GPIO_MAP remap)
{
	return can_gpio_map(Port, remap);
}

uint8 AstraCAN::fifo_ready(CAN_FIFO fifo)
{
	return can_fifo_ready(Port, fifo);
}


AstraCAN::AstraCAN()
{

}

AstraCAN::AstraCAN(CAN_Port* CANx)
{
	Port = CANx;
}

AstraCAN::AstraCAN(CAN_GPIO_MAP remap, ASTRA_CAN_BUS bus, ROLE role)
{
	Port = CAN1_BASE;
	this.bus = bus;
	this.role = role;	
	this.map(remap);
}

	// MS CAN only:
	void AstraCAN::volumeDown(void){
	}