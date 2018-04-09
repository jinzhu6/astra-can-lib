
void log(String s){
	#ifdef DEBUG
	Serial2.print(millis());
	Serial2.print(" ; ");
	Serial2.println(s);
	#endif
}

void blink(int times)
{// use to debug
  for (int i=0;i<times;++i)
  {
      log("blinking");
      digitalWrite(PC13, LOW);    // turn the onboard LED on
      delay(50);
      digitalWrite(PC13, HIGH);   // turn the LED off 
      delay(100);
  } 
}
// end blink(int times)