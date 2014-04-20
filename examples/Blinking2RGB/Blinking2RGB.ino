 
#include "blinky.h"

blinky led;
int delayLED = 1000;

void setup()
{
  led.init(0,3,13,6,true);  // Left LED using pin 3,5 and 6. It's a Common Anode, so invert is True 
  led.init(1,9,10,11,true);  // Right LED using pin 9,10 and 11. It's a Common Anode, so invert is True
  
  
  led.adjust(0,80,80,120, true);
  led.adjust(1,80,80,120, true);
  
  led.set(0,255,255,255,1000);   
  led.set(1,255,255,255,1000);  
  
  delay(5000);  
}

void loop()
{
 
  led.set(0,255,255,255,delayLED);  // led.set ( LED nr, Red, Green ,Blue, Transition time in ms ) 
  led.set(1,255,255,255,delayLED);  
  while(led.isAnyBusy()){} 			// led.isAnyBusy() returns true while any LED is transitioning
  delay(delayLED);  
  
  led.set(0,255,0,255,delayLED);   
  led.set(1,255,0,255,delayLED);  
  while(led.isAnyBusy()){} 
  delay(delayLED);  
  
  led.set(0,255,255,0,delayLED);   
  led.set(1,255,255,0,delayLED);  
  while(led.isAnyBusy()){} 
  delay(delayLED);  
  
  led.set(0,0,255,255,delayLED);   
  led.set(1,0,255,255,delayLED);  
  while(led.isAnyBusy()){} 
  delay(delayLED);  
  
  led.set(0,0,0,255,delayLED);   
  led.set(1,0,0,255,delayLED);  
  while(led.isAnyBusy()){} 
  delay(delayLED);  
  
  for (int x = 0; x<100 ; x++)
  { 
	  led.set(0,255,0,0,delayLED);   
	  led.set(1,0,0,255,delayLED);  
	  while(led.isAnyBusy()){} 
	  delay(delayLED);  
  
	  led.set(0,0,255,0,delayLED);   
	  led.set(1,255,0,0,delayLED);  
	  while(led.isAnyBusy()){} 
	  delay(delayLED);  
  
	  led.set(0,0,0,255,delayLED);   
	  led.set(1,0,255,0,delayLED);  
	  while(led.isAnyBusy()){} 
	  delay(delayLED);  

	  led.set(0,255,255,0,delayLED);   
	  led.set(1,255,0,255,delayLED);  
	  while(led.isAnyBusy()){} 
	  delay(delayLED);  
  
	  led.set(0,0,255,255,delayLED);   
	  led.set(1,255,255,0,delayLED);  
	  while(led.isAnyBusy()){} 
	  delay(delayLED);  
  
	  led.set(0,255,0,255,delayLED);   
	  led.set(1,0,255,255,delayLED);  
	  while(led.isAnyBusy()){} 
	  delay(delayLED);  
  }  
  led.set(0,0,0,255,delayLED);   
  led.set(1,0,0,255,delayLED);  
  while(led.isAnyBusy()){} 
  delay(delayLED);  
  
}



