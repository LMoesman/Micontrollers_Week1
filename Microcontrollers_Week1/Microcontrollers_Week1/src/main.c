/*
 * main.c
 *
 * Created: 2-2-2018 11:39:10
 *  Author: Lars Moesman & Rick Verstraten
 */ 

#include "main.h"
#include <avr/io.h>
#include <util/delay.h>

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
Author	:		dkroeske@gmail.com
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************/
int main( void )
/*
short:			main() loop, entry point of executable
inputs:
outputs:
notes:			Looping forever, flipping bits on PORTD
Version :    	DMK, Initial code
*******************************************************************/
{
	
	while (1)
	{
		ExecuteB2();
	}

	return 1;
}

void ExecuteB2()
/*
short:			main() loop, entry point of executable
inputs:
outputs:
notes:			Looping forever, flipping bits on PORTD
Version :    	DMK, Initial code
*******************************************************************/
{
	DDRD = 0b11111111;	//all ports of D are output now
	PORTD = 0x06;		//pin 6 and 7 are turned on 0b00000110  
	wait(500);
	PORTD = 0x00;		//all pins are turned off
	wait(500);
}

