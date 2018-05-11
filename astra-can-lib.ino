#include "lib/AstraCAN.h"
//#include <HardwareCAN.h>


#define DEBUG

// use up to 14 filters if you will process only few ID's
// uint32 lsFilters[] = {0x170, 0x160};

// here I state that ls is the main bus to operate on
// AstraCAN ls(CAN_GPIO_PA11_PA12, LS, PRIMARY, lsFilters);
//AstraCAN ls(CAN_GPIO_PA11_PA12, LS);
AstraCAN ls = AstraCAN();
// HardwareCAN ls(CAN1_BASE);
// ms will be secondary just to send messages occasionally
// AstraCAN ms(CAN_GPIO_PB8_PB9, MS, SECONDARY);
// locate memory for the incoming message  
CanMsg *inMsg;
CAN_STATUS stat ;
int emptyMessagesCount = 0;
int processedMessagesCount = 0;

void setup(){
	Serial2.begin(115200);
	pinMode(PC13, OUTPUT);
	blink(3);
	Serial2.println("Starting program. Setup.");
	// приравнять лог = сериал2 можно?
	blink(3);
	stat = ls.begin();	
	log("LS started with status "+ String(stat));
	showEcn(0x12,0x34,0x56);

}

void loop(){
	log("=====starting loop=====");
	#ifdef DEBUG
	delay(300);
	#endif

	if ((inMsg = ls.recv())!=NULL) {
		processedMessagesCount++;
		log("LS CAN message received. Count:" + String(processedMessagesCount));
		// обработка входящего сообщения и запуск функций (переключение состояния) либо расстановка флагов?
    log("--before triggers--");
	checkLsTriggers();
	log("--blafter triggers, before flags--");
	checkFlags();
	log("--after flags--");
	} else {
		emptyMessagesCount++;
		log("No message in queue. Empty messages count: "+ String(emptyMessagesCount)); // будет гадить в лог!!
	}
	
}