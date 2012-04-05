/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/

void sndA(void);

int main(int argc, char **argv)
{
	//kprintf("Hello World!\n");

	/*CS 354 Spring 2012*/
	/*Lab 1: Getting Acquainted with XINU*/
	/*Created by : Wilson Sumanang
	  Date       : 4 February 2012*/

	pid32 pid;

	for(pid = 0 ; pid < NPROC-1 ; pid++){
		print_proc_info(pid);
	}
	
	resume(create(sndA, 1024, 20, "process 1", 0));
	resume(create(sndA, 1024, 20, "process 2", 0));
	
	for(pid = 0 ; pid < NPROC-1 ; pid++){
		print_proc_info(pid);
	}
	
	return OK;
}

void sndA(void)
{
	sleep(10);
}
