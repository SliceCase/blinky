blinky
======

Blinky, an Ardunio library for the SliceCase Blinky.
If blinks or fades RGB LED's.

Created as a starting place for exploring how to simply blink a RGB LED with minimal code from the Arduino Sketch.
The library uses a timer / interupt to be able to continue dimming the LED's while the regular code keeps running.

The library is written for two LED's, but can be expanded by increasing '#define LEDs 2' in blinky.cpp to whatever amount needed.

**init**		(id, pin red, pin green, pin blue, is inverted)  
Example: 
	init(0,3,13,6,true);  
Setup LED nr 0, red LED pin on 3, green LED pin on 13, blue LED pin on 6, turn on inversion)  
Inversion means that setting value 255 will result in 0, e.g. 255 - the value.  
This is needed if using LED's with common anode / common +Vcc.  

**adjust**		(id, adjust value red, adjust value green, adjust value blue, is inverted)  
Example: 
	adjust(0,80,80,120, true);  
Adjust the strength of the individual LED's. Can be used to balance the total intensity of the LED's or to balance the colours.  
Works by setting the maximum allowed values. When set'ing a value later then this will be done in relation to these values.  

**set**(if, value red, value green, value blue, time in ms)  
Example: 
	set(0,255,128,0,5000);  
Move to the given values over the time set.  
Set LED nr 0, red = 255, green = 128, blue = 0, over 5000 milliseconds)  
Will start moving from the current colour to orange over 5 seconds.  
 
**isBusy**		(id)  
Will return true for if the given LED id is busy changing colour.  
Example, wait for LED id 0 to complete: 
	while (isBusy(0)==false){};  

**isAnyBusy**	()   
Will return true for if any LED's are busy changing colour.  
Example. wait for all LED's to complete: 
	while (isAnyBusy()==false){};  


 
Written for Ardunio Leonardo and SliceCase Blinky  
Created by Christoffer Järnåker, Two Hornets BV, 2014, www.SliceCase.com  
All code is delivered as-is with no guarantee or support.  
Part of the code derived from elsewhere and is marked appropriately.  
  
This is free software. You can redistribute it and/or modify it under  
the terms of Creative Commons Attribution 3.0 United States License.   
To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/   
or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.  
