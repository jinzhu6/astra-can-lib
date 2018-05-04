// тут запуск действий

/** 
 * шлет цифры на дисплей ошибок
 * три двухзначных числа
 */
void showEcn(uint8 d0, uint8 d1, uint8 d2){	
	log("==>sending message to ECN screen");
	ls.sendMessage(0x5e8,4,0x81, d0, d1, d2,0,0,0,0);
	 
	log("==sent");
}
//===========//
/**
 * моргнуть задними аварийками два раза
 */
void doThanks(){
	log("== doThanks ==");
	//уменьшить громкость на 1 обратно!
	log("volume down (temporary off)");
	// ms.volumeDown(); // в магнитоле нет ЛС кана, так что на модуле без лс уменьшать громкость надо вручную 
	//код... 
	// ls.recv(0x255); // не забыть, что нужно считать состояние всех фар!! если сообщение не сохраненно, то его получить..
	// ls.sendMessage();
	#ifdef DEBUG 
	blink(2);
	#endif
	delay(50);
	log("== end doThanks ==");
}
//============//
/**
 * издать звуковой сигнал 
 */
void beep(uint8 wait=0x1e, uint8 count=0x03, uint8 length=0x33){
	log("==>making beep!");
//пример сообщения ls.sendMessage(0x280,5,0x70,0x05,0x1e,0x03,0x33);
ls.sendMessage(0x280, 5, 0x70, 0x05, wait, count, length,0,0,0);
	log("== end making beep!");
	
}

void beep(){
	beep(0x1e, 0x03, 0x33);
}