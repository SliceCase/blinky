 
#include "blinky.h"

blinky led;
int delayLED = 1000;
int randLED1,randLED2,randLED3,randTime;

void setup()
{
  led.init(0,3,13,6,true);  // Left LED using pin 3,5 and 6. It's a Common Anode, so invert is True 
  led.init(1,9,10,11,true);  // Right LED using pin 9,10 and 11. It's a Common Anode, so invert is True
  
  
  led.adjust(0,80,80,120, true);
  led.adjust(1,80,80,120, true);
  
  led.set(0,255,255,255,1000);   
  led.set(1,255,255,255,1000);  
  
  randomSeed(analogRead(0));
  
  delay(1000);  
}

void loop()
{
   for (int x=0 ; x<2 ; x++)
  {
    if(led.isBusy(x) == false)
    {
      randLED1=random(1,255);
      randLED2=random(1,255);
      randLED3=random(1,255); 
      randTime=random(1000,10000); 
       
      led.set(x,randLED1,randLED2,randLED3,randTime);
    }
  }
  
}



