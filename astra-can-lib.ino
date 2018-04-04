#include "lib/astracan.h"

// use up to 14 filters if you will process only few ID's
// uint32 lsFilters[] = {0x170, 0x160};

// here I state that ls is the main bus to operate on
// AstraCAN ls(CAN_GPIO_PA11_PA12, LS, PRIMARY, lsFilters);
AstraCAN ls(CAN_GPIO_PA11_PA12, LS, PRIMARY);
// ms will be secondary just to send messages occasionally
AstraCAN ms(CAN_GPIO_PB8_PB9, MS, SECONDARY);
// locate memory for the incoming message  
CanMsg *inMsg;

void setup(){
ls.begin();	
}

void loop(){
	if ((inMsg = ls.receive())!=NULL) {
		// обработка входящего сообщения и запуск функций (переключение состояния) либо расстановка флагов?
	checkLsTriggers();
	checkFlages();
	
	}
	
}