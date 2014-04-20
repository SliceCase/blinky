/*
 *  blinky.h - Library for flashing LED's.
 *	Written for Arduino Leonardo and SliceCase Blinky
 *  Created by Christoffer Järnåker, Two Hornets BV, 2014.
  
 *  This is free software. You can redistribute it and/or modify it under
 *  the terms of Creative Commons Attribution 3.0 United States License. 
 *  To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ 
 *  or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
*/
#ifndef blinky_h
#define blinky_h 

#include "Arduino.h" 


class blinky
{
  public: 
	void init(unsigned short LEDnr,unsigned short Rpin, unsigned short Gpin, unsigned short Bpin, bool invert);
    void adjust(unsigned short LEDnr,unsigned short Rmax, unsigned short Gmax, unsigned short Bmax, bool invert);
    void set(unsigned short LEDnr,unsigned short Rvalue, unsigned short Gvalue, unsigned short Bvalue, unsigned short time);
	unsigned short clip(unsigned short value); 
	bool isBusy(unsigned short LEDnr);
    bool isAnyBusy();
    static void callback(); 
	  
  private:
};
#include <avr/io.h>
#include <avr/interrupt.h>

#define RESOLUTION 65536    // Timer3 is 16 bit
//#define RESOLUTION 1024    // Timer4 is 10 bit

class TimerThree
{
  public:
  
    // properties
    unsigned int pwmPeriod;
    unsigned char clockSelectBits;

    // methods
    void initialize(long microseconds=1000000);
    void start();
    void stop();
    void restart(); 
    void attachInterrupt(void (*isr)(), long microseconds=-1);
    void detachInterrupt();
    void setPeriod(long microseconds); 
    void (*isrCallback)();
};

extern TimerThree Timer3;

#endif
