/* pipcreate.c - pipcreate */

#include <xinu.h>

local pipid32 newpip(void);

/*------------------------------------------------------------------------
 *  pipcreate  -  Creates a pipe return the pipe ID
A process (neither the producer process nor the consumer process) creates a pipe using this system call, which returns the pipe ID pipid32 if the process is able to find an available pipe from system and setup the appropriate state variables. On success, it puts the pipe in "used" state. You need to think about the appropriate state variables required for a pipe, and also about where this state needs to be stored. The system call returns SYSERR if the process is unable to allocate a pipe because the all pipe are not available. 
 *------------------------------------------------------------------------
 */
syscall pipcreate(void)
{
	
	intmask mask;				/* interrupt mask				*/
	pipid32 pip;				/* pipe id					*/

	mask = disable();			/* disable interrupts at start of function	*/
	
	pip = newpip();
	pipcount++;				/* increase pipcount				*/	
	kprintf("--------Successfull Creating Pipe--------\n\r");
	restore(mask);				/* restore interrupts before normal return	*/
	return pip;
}

local pipid32 newpip(void)
{
	int32 	i;				/* iterate through all pipes 			*/
	static	pipid32 nextpip = 1;		/* position to try				*/
	for(i = 0 ; i < NPIPE ; i++) {
		nextpip %= NPROC;		/* wrap around to beginning */
		if (piptab[nextpip].pipstate == PIPE_FREE) {
			piptab[nextpip].pipstate = PIPE_USED;
			piptab[nextpip].owner = (pid32)getpid();
			return nextpip++;
		} else {
			nextpip++;
		}
	}
	return (pipid32)SYSERR;
}
