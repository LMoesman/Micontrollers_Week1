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
void ExecuteB3(int *state)
/* 
short:			Checks if button if pressed and activates animation
inputs:			int *state(the state of the button press)
outputs:		
notes:			state = 0 when button is not pressed yet and state = 1 when the button is pressed
Version :    	1.0
Author	:		Lars Moesman & Rick Verstraten
*******************************************************************/
{
	DDRD = 0b10000000;
	DDRC = 0b11111110;
	if(PINC == 0b00000001 || *state == 1) {
		PORTD = 0x80;
		wait(500);
		PORTD = 0x00;
		wait(500);
		*state = 1;
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
	int state = 0;
	
	while (1)
	{
		ExecuteB3(&state);
	}

	return 1;
}