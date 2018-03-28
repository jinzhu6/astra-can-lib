// I hope that Arduino IDE compiler will unite this with main file  
// this file contains patterns of LS messages that must be processed
checkLsTriggers(){
	int id = inMsg->ID;
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
		showEcn(123456);
	}
	else if (id == 0x000){
		// две бобышки вверх
	doThansk();
}