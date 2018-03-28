showEcn(value){
	// парсим на байты
	ls.SendCANmessage(0x108,8,0x03,msgD0,msgD0,0x00,msgD0,msgD0,0x00,0x00); 
}