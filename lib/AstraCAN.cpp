/**
 * @brief AstraCAN "wiring-like" api for CAN
 */

#include "wirish.h"
#include "utility/can.h"
#include "AstraCAN.h"


// Сначала конструкторы
AstraCAN::AstraCAN(CAN_GPIO_MAP remap, ASTRA_CAN_BUS bus){
	this.remap = remap;
	this.bus =	bus;
	Port = CAN1_BASE;
	this.mode = CAN_MODE_NORMAL;
	if (this.bus == LS) {
		this.speed = CAN_SPEED_33;
	} esleif (this.bus == MS){
		this.speed = CAN_SPEED_95;
	} esleif (this.bus == HS){
		this.speed = CAN_SPEED_500;
	} else {
		// bad
	}
	
}

/**
 * Активация, в том числе переключение настройки
 */
AstraCAN::activate(void){
	Serial.end();
	if (this.remap == CAN_GPIO_PA11_PA12) {
		afio_init(); // this will restart subsystem and make it work!		
	}
	Stat = can_gpio_map(Port, this.remap);
	Stat = can_set_irq_mode(Port);
	if (can_init(Port, 0, speed) == CAN_OK)
		Stat = can_set_mode(Port, this.mode);
	Stat = can_status();
	return Stat;
}

 

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

/**
 * @brief Initialize a CAN peripheral
 */
CAN_STATUS AstraCAN::begin(void)
{
	// внимание!!!! это лс кан по умолчанию!
	canBus.map(CAN_GPIO_PA11_PA12);
	return begin(CAN_SPEED_33, CAN_MODE_NORMAL);
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
void AstraCAN::sendMessage(long id, byte dlength, byte d0, byte d1, byte d2, byte d3, byte d4, byte d5, byte d6, byte d7)
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

CAN_TX_MBX  AstraCAN::CANsend(CanMsg *pmsg) // Should be moved to the library?!
{
  CAN_TX_MBX mbx;
  do 
  {
    mbx = canBus.send(pmsg) ;
  }
  while(mbx == CAN_TX_NO_MBX) ;       // Waiting outbound frames will eventually be sent, unless there is a CAN bus failure.
  return mbx ;
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


// AstraCAN::AstraCAN()
// {
// 	this.bus = LS;
// 	this.role = PRIMARY;	
// 	this.remap = CAN_GPIO_PA11_PA12;
// 	this.Port = CAN1_BASE;
// }

// AstraCAN::AstraCAN(CAN_Port* CANx)
// {
// 	Port = CANx;
// }

// AstraCAN::AstraCAN(CAN_Port* CANx, CAN_GPIO_MAP remap, ASTRA_CAN_BUS bus, ROLE role){
// 	Port = CANx;
// 	this.bus = bus;
// 	this.role = role;	
// 	this.remap = remap;
// 	this.filter(0,0,0);
//     this.set_irq_mode();
// }

// AstraCAN::    AstraCAN(CAN_Port* CANx, CAN_GPIO_MAP remap, ASTRA_CAN_BUS bus, ROLE role, uint32 filters[])
// {
// 	Port = CANx;
// 	this.bus = bus;
// 	this.role = role;	
// 	this.remap = remap;
// 	for (int i = 0; i < filters.length, i++){

// 	}
// }


// MS CAN only:
void AstraCAN::volumeDown(void){
}