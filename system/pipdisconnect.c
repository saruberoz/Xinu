/* pipdisconnect.c - pipdisconnect */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipdisconnect  -  Disconnect two processes from a pipe
The call returns OK, if the pipe is in reasonable state, and SYSERR otherwise. Note that only the owner of the pipe can call disconnect. If a non-owner tries to delete, then SYSERR needs to be returned. 
 *------------------------------------------------------------------------
 */
syscall pipdisconnect(
	 pipid32		pip		/* ID of pipe to delete	*/
	)
{	
	intmask mask;				/* interrupt mask				*/
	struct	pipent	*pipptr;

	mask = disable();			/* disable interrupts at start of function	*/
	
	if(isbadpip(pip)) {
		restore(mask);			/* restore interrupts before error return	*/
		return (pipid32) (SYSERR);
	}
	
	pipptr = &piptab[pip];
	
	if(pipptr->pipstate != PIPE_CONNECTED){	/* make sure that it is the correct pipe	*/
		restore(mask);			/* restore interrupts before error return	*/
		return (pipid32) (SYSERR);
	}
	
	if(pipptr->owner != (pid32)getpid()){	/* make sure only owner can connect to the pipe	*/
		restore(mask);			/* restore interrupts before error return	*/
		return (pipid32) (SYSERR);
	}

	pipptr->pipstate = PIPE_USED;
	pipptr->reader = 0;
	pipptr->writer = 0;
	
	semdelete(pipptr->emptySem);
	semdelete(pipptr->fullSem);

	restore(mask);				/* restore interrupts before normal return	*/
	return OK;		
}
