/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/

void progA(void);

int main(int argc, char **argv)
{
	/*CS 354 Spring 2012*/
	/*Lab 2: Round Robin Scheduling*/
	/*Created by : Wilson Sumanang
	  Date       : 12 February 2012*/	
	kprintf("Task 1:\n");
	
	resume(create(progA, 1024, 19, "program A", 0));
	resume(create(progA, 1024, 19, "program A", 0));

	//int i = 0;
//	while(i < 100) {
	while(1) {
		kprintf("%c", 'D');
		//for(i=0;i<10000;i++);
//		i++;
	}
	return OK;
}

char c = 'P';
void progA(void)
{
	//int i = 0;
//	while(i < 100) {
	while(1) {
		kprintf("%c", c);
		//for(i=0;i<10000;i++);
//		i++;
	}
}
