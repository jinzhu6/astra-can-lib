// I hope that Arduino IDE ? LS messages that must be processed
void checkLsTriggers(){
	log("--- Start checking triggers ---");
	uint32 id = inMsg->ID;
	uint8* b = inMsg->Data; //надеюсь, сработает, для упрощения кода
	// разбор сообщений в зависимости от ID 
	if (id==0x160){
		log("Id 0x160 found - keyholder");
		// buttons on key holder
		if (b[0]==0x00 and b[1]==0x00) {
			// some logic here
			log("b[0]==0x00 and b[1]==0x00") 
			//ms.sendMessage(0x100,2,0x00,0x01); //WTF? пока без МС
		}
	}
	else if (id == 0x170){
		// положение ключа зажигания
		log("Id 0x170 found - ignition lock");
		}
	else if (id == 0x000){
		log("It cannot be true!")
		// комбинация для показа чего-нибудь в окошке ошибок
		ls.sendMessage(0x100,0);
		showEcn(0x12,0x34,0x56);
	}
	else if (id == 0x175){
		log("Id 0x175 found - buttons around steering wheel");		
		// рулевая колонка
		
		if (/*две бобышки вверх*/
					(b[5] == 0x11) /* на самом деле надо побитовое И !! */
					and
					(b[6]==0x1f)
					and
					(b[7]==0x01)
				) {
					log("two thumbs up detected");
					doThanks();
				}
	}
	else if (id == 0x305){
		//кнопки управления фарами
		log("Id 0x305 detected - lights control")
		if (/*фары не включены совсем*/
					b[2]==0x00) {
						log("b[2]==0x00, lights are all off. Setting the flag 1");
						flagLightsOff=1;
					}else{
						log("b[2]!=0x00, lights are NOT all off. Setting the flag 0");
						flagLightsOff=0;
					}
		}
log("--- end of LS triggers check ---");
}


void checkFlags(){
log("--- Start of flags check ---");
	if (flagLightsOff and flagMove){
		log("flagLightsOff and flagMove detected. Should make a signal. Or simulate handbrake is on.")
		beep();
	}
log("--- end of flags check ---");
}