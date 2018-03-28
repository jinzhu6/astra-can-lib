// I hope that Arduino IDE compiler will unite this with main file  
// this file contains patterns of LS messages that must be processed
checkLsTriggers(){
	int id = inMsg->ID;
	
	if (id=0x170){
		// buttons on key holder
		if (inMsg->Data[0]==0x00 and inMsg->Data[1]==0x00) {
			// some logic here 
			ms.sendMessage(0x100,2,0x00,0x01);
		}
	}
	else if (id = 160){
		//something else
		ls.sendMessage(0x100,0);
		ls.showEcn(123456);
	}
}

