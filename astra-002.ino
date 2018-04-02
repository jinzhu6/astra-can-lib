// тут запуск действий

/** 
 * шлет цифры на дисплей ошибок
 * три двухзначных числа
 */
void showEcn(int[] d){	ls.SendCANmessage(0x5e8,4,0x81,d[0], d[1], d[2]); 
}
//===========//
/**
 * моргнуть задними аварийками два раза
 */
void doThansk(){
	//уменьшить громкость на 1 обратно!
	ms.volumeDown(); // в магнитоле нет ЛС кана, так что на модуле без лс уменьшать громкость надо вручную 
	//код... 
	ls.receive(0x)// не забыть, что нужно считать состояние всех фар!! если сообщение не сохраненно, то его получить..
	ls.SendCANmessage();
	delay();
}
//============//
/**
 * издать звуковой сигнал 
 */
void beep(int wait=0x1e, int count=0x03, int length=0x33){
//пример сообщения ls.SendCANmessage(0x280,5,0x70,0x05,0x1e,0x03,0x33);
ls.SendCANmessage(0x280, 5, 0x70, 0x05, wait, count, length);
	
}