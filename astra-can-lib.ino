// #include <HardwareCAN.h>
#include "lib/EmptyCan.h"
/*
 * 
 */

#define DEBUG

// use up to 14 filters if you will process only few ID's
// uint32 lsFilters[] = {0x170, 0x160};

// here I state that ls is the main bus to operate on
// AstraCAN ls(CAN_GPIO_PA11_PA12, LS, PRIMARY, lsFilters);
//AstraCAN ls(CAN_GPIO_PA11_PA12, LS);
EmptyCan ls = EmptyCan();
// ms will be secondary just to send messages occasionally
// AstraCAN ms(CAN_GPIO_PB8_PB9, MS, SECONDARY);
// locate memory for the incoming message  
CanMsg *inMsg;
CAN_STATUS stat ;
int emptyMessagesCount = 0;
int processedMessagesCount = 0;
bool flagLightsOff = 0;
bool flagMove = 0;


void setup(){

    #ifdef DEBUG
    flagMove = 1;
    #endif

	Serial2.begin(115200);
	pinMode(PC13, OUTPUT);
	blink(3);
	Serial2.println("Starting program. Setup.");
	// приравнять лог = сериал2 можно?
	blink(3);
	stat = ls.begin();
	ls.filter(0, 0, 0);
	ls.set_irq_mode();
	log("LS started with status "+ String(stat));
	panelCheck();
	delay(300);
	showEcn(0x12,0x34,0x56);
    delay(1000);
}

void loop(){
	log("=====starting loop=====");
	#ifdef DEBUG
	log("Debug delay");
	delay(1000);
	#endif

	if ((inMsg = ls.recv())!=NULL) {
		processedMessagesCount++;
		log("LS CAN message received.");
		// обработка входящего сообщения и запуск функций (переключение состояния) либо расстановка флагов?
        log("--before triggers--");
        checkLsTriggers();
        log("--after triggers--");
        ls.free();
        log("--remove message from incoming box--");
	} else {
		emptyMessagesCount++;
		log("No message in queue.");
	}

	log("--before flags--");
	checkFlags();
	log("--after flags--");

	log("Received messages count:" + String(processedMessagesCount));
	log("Empty    messages count: "+ String(emptyMessagesCount));
}
