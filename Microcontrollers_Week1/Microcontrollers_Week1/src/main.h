/*
 * main.h
 *
 * Created: 2-2-2018 11:39:41
 *  Author: Lars Moesman & Rick Verstraten
 */ 


#ifndef MAIN_H_
#define MAIN_H_
#define F_CPU 8000000

typedef struct{
		char data;
		int wait;
	}LOOPLIGHT_PATTERN;

void wait(int);

void ExecuteB2(void);
void ExecuteB3(void);
void ExecuteB5(void);
void ExecuteB4knightRider(int*);


#endif /* MAIN_H_ */