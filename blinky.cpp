/*
 *  blinky.h - Library for flashing LED's.
 *	Written for Arduino Leonardo and SliceCase Blinky
 *  Created by Christoffer Järnåker, Two Hornets BV, 2014.
  
 *  This is free software. You can redistribute it and/or modify it under
 *  the terms of Creative Commons Attribution 3.0 United States License. 
 *  To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ 
 *  or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
*/

#include "Arduino.h"
#include "blinky.h"

#define LEDs 2

volatile unsigned short _rpin[LEDs];
volatile unsigned short _gpin[LEDs];
volatile unsigned short _bpin[LEDs];

volatile double _rval[LEDs];
volatile double _gval[LEDs];
volatile double _bval[LEDs];

volatile unsigned short _rmax[LEDs];
volatile unsigned short _gmax[LEDs];
volatile unsigned short _bmax[LEDs];

volatile double _radj[LEDs];
volatile double _gadj[LEDs];
volatile double _badj[LEDs];

volatile double _rtick[LEDs];
volatile double _gtick[LEDs];
volatile double _btick[LEDs];
  
volatile unsigned short _rtarget[LEDs];
volatile unsigned short _gtarget[LEDs];
volatile unsigned short _btarget[LEDs];

volatile bool active[LEDs];
volatile bool busyAny;

volatile unsigned short _stepsPerSecond;

volatile bool _invert[LEDs]; 
volatile bool _init[LEDs];
  
void blinky::init(unsigned short LEDnr, unsigned short Rpin, unsigned short Gpin, unsigned short Bpin, bool invert)
  {  
    _rpin[LEDnr] = Rpin;
    _gpin[LEDnr] = Gpin;
    _bpin[LEDnr] = Bpin;
	_rmax[LEDnr] = 255;
	_gmax[LEDnr] = 255;
	_bmax[LEDnr] = 255;
	_radj[LEDnr] = 1;
	_gadj[LEDnr] = 1;
	_badj[LEDnr] = 1;
	analogWrite(_rpin[LEDnr], 255 * (int)invert);
	analogWrite(_gpin[LEDnr], 255 * (int)invert);
	analogWrite(_bpin[LEDnr], 255 * (int)invert);
	pinMode(_rpin[LEDnr], OUTPUT);
	pinMode(_gpin[LEDnr], OUTPUT);
	pinMode(_bpin[LEDnr], OUTPUT);
    _invert[LEDnr] = invert;
	_init[LEDnr] = true;
	set(LEDnr,0,0,0,0);
	
	_stepsPerSecond = 40;
	//Timer3.initialize(25000); 
	Timer3.initialize(((double)1/_stepsPerSecond)*1000000);
	Timer3.attachInterrupt(callback);  
  }   

void blinky::adjust(unsigned short LEDnr, unsigned short Rmax, unsigned short Gmax, unsigned short Bmax, bool invert)
{
	_rmax[LEDnr] = clip(Rmax);
	_gmax[LEDnr] = clip(Gmax);
	_bmax[LEDnr] = clip(Bmax);
	
	_radj[LEDnr] = _rmax[LEDnr] == 0 ? 0 : (double)_rmax[LEDnr] / 255;
	_gadj[LEDnr] = _gmax[LEDnr] == 0 ? 0 : (double)_gmax[LEDnr] / 255;
	_badj[LEDnr] = _bmax[LEDnr] == 0 ? 0 : (double)_bmax[LEDnr] / 255;
	
	_invert[LEDnr] = invert;

}
void blinky::set(unsigned short LEDnr, unsigned short Rvalue, unsigned short Gvalue, unsigned short Bvalue, unsigned short time)
{
	_rtarget[LEDnr] = clip(Rvalue);
	_gtarget[LEDnr] = clip(Gvalue);
	_btarget[LEDnr] = clip(Bvalue);

	if (time == 0) time = 1;
	
	_rtick[LEDnr] = ((double)_rtarget[LEDnr] - _rval[LEDnr]) * 
			((double)1 / (double)_stepsPerSecond) /  
			((double)time / 1000);
	_gtick[LEDnr] = ((double)_gtarget[LEDnr] - _gval[LEDnr]) * 
			((double)1 / (double)_stepsPerSecond) /  
			((double)time / 1000);
	_btick[LEDnr] = ((double)_btarget[LEDnr] - _bval[LEDnr]) * 
			((double)1 / (double)_stepsPerSecond) /  
			((double)time / 1000);
	//Serial.println(_rtick[LEDnr]);
	//Serial.println("LED " + (String)(int)LEDnr + "  " + (String)(int)_rtick[LEDnr] + " " + (String)(int)_gtick[LEDnr] + " " + (String)(int)_btick[LEDnr]); 
		
	if (abs(_rtick[LEDnr])+abs(_gtick[LEDnr])+abs(_btick[LEDnr]) != 0) active[LEDnr] = true;  
	
}	
unsigned short blinky::clip(unsigned short value)
{	 
	return value <= 0 ? 0 : value >= 255 ? 255 : value;
}	
bool blinky::isBusy(unsigned short LEDnr)
{
	return active[LEDnr];
}
bool blinky::isAnyBusy()
{	
	busyAny = false;
	for (unsigned short x = 0;x < LEDs;x++)
	{
		if (active[x]==true)
		{
			busyAny = true;
			//Serial.println("LED " + (String)(int)x + " is active");
		}
	}
	return busyAny;
}
void blinky::callback()
{    
 
	double Rvalue;
	double Gvalue;
	double Bvalue;
	for (unsigned short x = 0 ; x < LEDs ; x++)
	{	//Serial.println("LED: " + (String)x);
		if (!active[x]) 
		{
			//Serial.println("Not active");
			continue; 
		}
		if (!_init[x])
		{
			//Serial.println("Not initiated");
			continue;
		}
		
		Rvalue = (double)_rval[x] + _rtick[x]; 
		if (_rtick[x] > 0 && Rvalue > _rtarget[x]) Rvalue = _rtarget[x];
		if (_rtick[x] < 0 && Rvalue < _rtarget[x]) Rvalue = _rtarget[x];
		
		Gvalue = (double)_gval[x] + _gtick[x]; 
		if (_gtick[x] > 0 && Gvalue > _gtarget[x]) Gvalue = _gtarget[x];
		if (_gtick[x] < 0 && Gvalue < _gtarget[x]) Gvalue = _gtarget[x];
		
		Bvalue = (double)_bval[x] + _btick[x]; 
		if (_btick[x] > 0 && Bvalue > _btarget[x]) Bvalue = _btarget[x];
		if (_btick[x] < 0 && Bvalue < _btarget[x]) Bvalue = _btarget[x];
		 
		_rval[x] = Rvalue; 
		_gval[x] = Gvalue; 
		_bval[x] = Bvalue; 
		
		Rvalue = Rvalue * _radj[x];
		Gvalue = Gvalue * _gadj[x];
		Bvalue = Bvalue * _badj[x];
		
		if (_invert[x])
		{
			Rvalue = 255-Rvalue;
			Gvalue = 255-Gvalue;
			Bvalue = 255-Bvalue;
		} 
		//Serial.println("target " + (String)(int)_rtarget[x] + " " + (String)(int)_gtarget[x] + " " + (String)(int)_btarget[x]); 
		//Serial.println("@      " + (String)(int)_rval[x] + " " + (String)(int)_gval[x] + " " + (String)(int)_bval[x]); 
		analogWrite(_rpin[x], Rvalue);
		analogWrite(_gpin[x], Gvalue);
		analogWrite(_bpin[x], Bvalue); 

		if (_rtarget[x] == (unsigned short)_rval[x] && _gtarget[x] == (unsigned short)_gval[x] && _btarget[x] == (unsigned short)_bval[x] )
		{
			//Serial.println("LED " + (String)(int)x + " is done"); 
			active[x] = false;
		} 
	} 
	  //Serial.println("busyAny = " + (String)busyAny); 
} 
/*
 *  Interrupt and PWM utilities for 16 bit Timer3 on ATmega168/328
 *  Original code by Jesse Tane for http://labs.ideo.com August 2008
 *  Modified March 2009 by Jérôme Despatis and Jesse Tane for ATmega328 support
 *  Modified June 2009 by Michael Polli and Jesse Tane to fix a bug in setPeriod() which caused the timer to stop
 *  Modified Oct 2009 by Dan Clemens to work with timer3 of the ATMega1280 or Arduino Mega
 *  Modified Apr 2014 by C Järnåker to be included in the blinky sketch package.
 *
 *  This is free software. You can redistribute it and/or modify it under
 *  the terms of Creative Commons Attribution 3.0 United States License. 
 *  To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ 
 *  or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 *
 */ 

TimerThree Timer3;              // preinstatiate

ISR(TIMER3_OVF_vect)          // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  Timer3.isrCallback();
}

void TimerThree::initialize(long microseconds)
{
  TCCR3A = 0;                 // clear control register A 
  TCCR3B = _BV(WGM13);        // set mode as phase and frequency correct pwm, stop the timer
  setPeriod(microseconds);
}

void TimerThree::setPeriod(long microseconds)
{
  long cycles = (F_CPU * microseconds) / 2000000;                                // the counter runs backwards after TOP, interrupt is at BOTTOM so divide microseconds by 2
  if(cycles < RESOLUTION)              clockSelectBits = _BV(CS10);              // no prescale, full xtal
  else if((cycles >>= 3) < RESOLUTION) clockSelectBits = _BV(CS11);              // prescale by /8
  else if((cycles >>= 3) < RESOLUTION) clockSelectBits = _BV(CS11) | _BV(CS10);  // prescale by /64
  else if((cycles >>= 2) < RESOLUTION) clockSelectBits = _BV(CS12);              // prescale by /256
  else if((cycles >>= 2) < RESOLUTION) clockSelectBits = _BV(CS12) | _BV(CS10);  // prescale by /1024
  else        cycles = RESOLUTION - 1, clockSelectBits = _BV(CS12) | _BV(CS10);  // request was out of bounds, set as maximum
  ICR3 = pwmPeriod = cycles;                                                     // ICR1 is TOP in p & f correct pwm mode
  TCCR3B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
  TCCR3B |= clockSelectBits;                                                     // reset clock select register
}
 
  

void TimerThree::attachInterrupt(void (*isr)(), long microseconds)
{
  if(microseconds > 0) setPeriod(microseconds);
  isrCallback = isr;                                       // register the user's callback with the real ISR
  TIMSK3 = _BV(TOIE1);                                     // sets the timer overflow interrupt enable bit
  sei();                                                   // ensures that interrupts are globally enabled
  start(); 
}

void TimerThree::detachInterrupt()
{
  TIMSK3 &= ~_BV(TOIE1);                                   // clears the timer overflow interrupt enable bit 
}

void TimerThree::start()
{
  TCCR3B |= clockSelectBits;
}

void TimerThree::stop()
{
  TCCR3B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));          // clears all clock selects bits
}

void TimerThree::restart()
{
  TCNT3 = 0;
}
