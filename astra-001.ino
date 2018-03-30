// I hope that Arduino IDE compiler will unite this with main file  
// this file contains patterns of LS messages that must be processed
checkLsTriggers(){
	int id = inMsg->ID;
	int[8] b = inMsg->Data; //надеюсь, сработает, для упрощения кода
	// разбор сообщений в зависимости от ID 
	if (id==0x160){
		// buttons on key holder
		if (inMsg->Data[0]==0x00 and inMsg->Data[1]==0x00) {
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
					(inMsg->Data[5] == 0x11) // на самом деле надо побитовое И !!
					and
					(inMsg->Data[6]==0x1f)
					and
					(inMsg->Data[7]==0x01)
				) {
					doThansk();
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