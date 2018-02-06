/*
 * main.c
 *
 * Created: 2-2-2018 11:39:10
 *  Author: Lars Moesman & Rick Verstraten
 */ 

#include "main.h"
#include <avr/io.h>
#include <util/delay.h>

LOOPLIGHT_PATTERN pattern1[] = {{0x01, 50}, {0x02, 50}, {0x04, 50}, {0x08, 50}, {0x10, 50}, {0x20, 50}, {0x40, 50}, {0x80, 50}};
LOOPLIGHT_PATTERN pattern2[] = {{0x18, 100}, {0x3c, 100}, {0x66, 100}, {0xc3, 100}, {0xc3, 100}, {0x66, 100}, {0x3c, 100}, {0x18, 100}, {0x00, 200},
	{0x01, 100}, {0x05, 100}, {0x15, 100}, {0x55, 200}, {0xd5, 100}, {0xf5, 100}, {0xfd, 100}, {0xff, 200},
	{0xc3, 100}, {0x66, 100}, {0x3c, 100}, {0x18, 100}, {0x00, 200}	};
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
void ExecuteB2()
/*
short:			ExecuteB2(), blinks pin 6 and 7
inputs:
outputs:
notes:
Version :    	V1.0
Author:			Lars Moesman & Rick Verstraten
*******************************************************************/
{
	DDRD = 0b11111111;	//all ports of D are output now
	PORTD = 0x80;		//pin 6 and 7 are turned on 0b11000000
	wait(500);
	PORTD = 0x40;		//all pins are turned off
	wait(500);
}


/******************************************************************/
void ExecuteB3()
/* 
short:			Checks if button if pressed and activates animation
inputs:			
outputs:		
notes:			
Version :    	1.0
Author	:		Lars Moesman & Rick Verstraten
*******************************************************************/
{
	DDRD = 0b10000000;
	DDRC = 0b11111110;
	if(PINC == 0b00000001) {
		PORTD = 0x80;
		wait(500);
		PORTD = 0x00;
		wait(500);
	}
	
}


/******************************************************************/
void ExecuteB5()
/*
short:			Executes animation from one of the pattern arrays defined in this file
inputs:			
outputs:
notes:			you can choose from pattern1(looping) or pattern2(custom animation)
Version :    	1.0
Author	:		Lars Moesman & Rick Verstraten
*******************************************************************/
{
	DDRD = 0b11111111;
	int index;
	
	for(index = 0;index < (sizeof(pattern2) / sizeof(pattern2[0]));index++) {
		PORTD = pattern2[index].data;
		wait(pattern2[index].wait);
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
		//ExecuteB2();
		//ExecuteB3();
		//ExecuteB5();
	}

	return 1;
}


