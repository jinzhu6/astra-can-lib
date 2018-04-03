// I hope that Arduino IDE ? LS messages that must be processed
void checkLsTriggers(){
	int id = inMsg->ID;
	uint8 b[8] = inMsg->Data; //надеюсь, сработает, для упрощения кода
	// разбор сообщений в зависимости от ID 
	if (id==0x160){
		// buttons on key holder
		if (b[0]==0x00 and b[1]==0x00) {
			// some logic here 
			ms.sendMessage(0x100,2,0x00,0x01);
		}
	}
	else if (id == 0x170){
		// положение ключа зажигания
		}
	else if (id == 0x000){
		// комбинация для показа чего-нибудь в окошке ошибок
		ls.sendMessage(0x100,0);
		showEcn({0x12,0x34,0x56});
	}
	else if (id == 0x175){
		// рулевая колонка
		
		if (/*две бобышки вверх*/
					(b[5] == 0x11) // на самом деле надо побитовое И !!
					and
					(b[6]==0x1f)
					and
					(b[7]==0x01)
				) {
					doThanks();
				}
	}
	else if (id == 0x305){
		//кнопки управления фарами
		
		if (/*фары не включены совсем*/
					b[2]==0x00) {
						flagLightsOff=1;
					}else{
						flagLightsOff=0;
					}
		}
}


checkFlags(){
	if (flagLightsOff and flagMove){
		beep();
	}
}