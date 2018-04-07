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
CAN_STATUS stat ;

void setup(){
	Serial2.start(115200);
	// приравнять лог = сериал2 можно?
	log("Starting program. Setup.");
	stat = ls.begin();	
	log("LS started with status "& stat);
}

void loop(){
	log("starting loop")
	if ((inMsg = ls.receive())!=NULL) {
		log("message received");
		// обработка входящего сообщения и запуск функций (переключение состояния) либо расстановка флагов?
log("--before triggers--");
	checkLsTriggers();
	log("--blafter triggers, before flags--");
	checkFlags();
	log("--after flags--");
	}
	
}