/*
 * main.c
 *
 * Created: 2-2-2018 11:39:10
 *  Author: Lars Moesman & Rick Verstraten
 */ 

#include "main.h"
#include <avr/io.h>
#include <util/delay.h>
#include <time.h>

LOOPLIGHT_PATTERN pattern1[] = {{0x01, 50}, {0x02, 50}, {0x04, 50}, {0x08, 50}, {0x10, 50}, {0x20, 50}, {0x40, 50}, {0x80, 50}};
LOOPLIGHT_PATTERN pattern2[] = {{0x18, 100}, {0x3c, 100}, {0x66, 100}, {0xc3, 100}, {0xc3, 100}, {0x66, 100}, {0x3c, 100}, {0x18, 100}, {0x00, 200},
	{0x01, 100}, {0x05, 100}, {0x15, 100}, {0x55, 200}, {0xd5, 100}, {0xf5, 100}, {0xfd, 100}, {0xff, 200},
	{0xc3, 100}, {0x66, 100}, {0x3c, 100}, {0x18, 100}, {0x00, 200}	};
const int waitState[2] = {1000, 250};

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
void customWait( int ms, int* state )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait) int* state (Is button pressed)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h state == 0 (button is not pressed), state ==1 (button is pressed)
Version :    	2.0
Author	:		dkroeske@gmail.com
Edited By:		Lars Moesman & Rick Verstraten
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
		if (CheckButton(state) == 1) {break;} //checks if button is pressed
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
void ExecuteB4knightRider(int* state)
/*
short:			Executes KITT animation
inputs:			int *state(direction of animation)
outputs:
notes:			state = 0 top to bottom and state = 1 bottom to top
Version :    	1.0
Author	:		Lars Moesman & Rick Verstraten
*******************************************************************/
{
	if(*state == 0){
		wait(85);			
		PORTD <<= 1;	//moves leds one place to the right
	}else{
		wait(85);
		PORTD >>= 1;	//moves leds one place to the left.
	}
	if(PORTD == 0xC0){*state = 1;}	//change state at the beginning and the end of PORTD
	if(PORTD == 0x03){*state = 0;}
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
		PORTD = pattern2[index].data;	//Sets pattern address from Array to port
		wait(pattern2[index].wait);
	}
	
}

int CheckButton(int *state) {
/*
short:			Checks if button is pressed
inputs:			int* state(state from button)
outputs:		int 1 or 0.
notes:			return 1 if button state is changed and 0 if not
Version :    	1.0
Author	:		Lars Moesman & Rick Verstraten
	*******************************************************************/
	DDRC = 0b11111110;
	if(PINC == 0b00000001) {
		*state = !*state;		//set state to 0 or 1 (boolean)
		return 1;
	}
	return 0;
}

int TranslatePins(int pin) {
/*
short:			Makes address for controlling the port or ddrd
inputs:			int pin(which pin has to be turned on or set to output)
outputs:		int translation(address for controlling port or ddrd)
notes:			
Version :    	1.0
Author	:		Lars Moesman & Rick Verstraten
	*******************************************************************/
	int translation = 0b00000001;	//Standard address to bitshift later(1 pin is always 1 in this method)
	translation <<= pin - 1;		//Bitshift so the right pin bit is set to 1
	return translation;
}

void ExecuteB6(int *state)
/*
short:			Executes blinking led with certain waits
inputs:			int* state(state from button)
outputs:
notes:			state 1 is button pressed, state 0 is button not pressed
Version :    	1.0
Author	:		Lars Moesman & Rick Verstraten
*******************************************************************/
{
	DDRD = 0b10000000;
	
	PORTD = 0x80;
	customWait(waitState[*state], state);
	PORTD = 0x00;
	customWait(waitState[*state], state);
	
}

void ExecuteB7b(int lednr)
/*
short:			Executes blinking led with certain waits
inputs:			int* state(state from button)
outputs:
notes:			state 1 is button pressed, state 0 is button not pressed
Version :    	1.0
Author	:		Lars Moesman & Rick Verstraten
*******************************************************************/
{
	int firstPin = (floor(lednr / 2)) + (lednr % 2);	//Calculates which pin (ascending way)is the first pin 
	int secondPin = (firstPin % PINS) + 1;				//Calculates which pin (ascending way)is the second pin 
	int thirdPin = firstPin - secondPin;				
	if (thirdPin > 0) {thirdPin *= -1;}					//Adjustment if third pin is negative
	thirdPin = (thirdPin % PINS) + 1;					//Calculates which pin is the pin that needs to be turned off(Input)
		
	int address = TranslatePins(firstPin) | TranslatePins(secondPin);	//Merge 2 addresses so it can be set to DDRD
	DDRD = address;
	
	if (lednr % 2 == 0) {
		PORTD = TranslatePins(secondPin);						//Even LED needs the second pin to be turned on
	}else{
		PORTD = TranslatePins(firstPin);						//Odd LED needs the first pin to be turned on
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

	int state = 0;	//state for switching shift direction.
	while (1)
	{
		//ExecuteB2();
		//ExecuteB3();

		//ExecuteB5();

		//ExecuteB4knightRider(&state);
		//ExecuteB6(&state);
		//ExecuteB7b(1);
	}
	
	return 1;
}


