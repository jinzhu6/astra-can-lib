// тут запуск действий

/** 
 * шлет цифры на дисплей ошибок
 * три двухзначных числа
 */
void showEcn(uint8 d0, uint8 d1, uint8 d2){	
	log("==>sending message to ECN screen");
	ls.sendMessage(0x5e8,8,0x81, d0, d1, d2,0x00,0x00,0x00,0x00);
	 
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
	delay(50);
	blink(2);
	showEcn(0xAB,0xCD,0xEF);
	delay(50);
	showEcn(0xAB,0xCD,0xEF);
//	ls.sendMessage(0x260,3,0x1F,0x43,0x7F); // аварийка хак
	ls.sendMessage(0x305,7,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00); // аварийка кнопка
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

void panelCheck(){
	log("==>making panelCheck!");
    ls.sendMessage(0x255, 8, 0x05, 0xAE, 0x06, 0x01, 0x8A,0x00,0x00,0x00);
    delay(50);
    ls.sendMessage(0x255, 8, 0x05, 0xAE, 0x07, 0x01, 0x7F,0x00,0x00,0x00);
    delay(50);
    ls.sendMessage(0x255, 8, 0x04, 0xAE, 0x08, 0x01, 0xFF,0x00,0x00,0x00);
    delay(500);
    ls.sendMessage(0x255, 8, 0x05, 0xAE, 0x07, 0x01, 0x00,0x00,0x00,0x00);
	log("== end making panelCheck!");
}