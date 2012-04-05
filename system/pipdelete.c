/* pipdelete.c - pipdelete */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipdelete  -  Release a pipe
the call a pipe ID as an argument. It should set the state of the pipe to "free" and return OK. After the call, the pipe should be ready for reallocation (i.e. the call should clear the buffer and reset associated variables). Note that only the owner of the pipe can delete. If a non-owner tries to delete, then SYSERR needs to be returned. 
 *------------------------------------------------------------------------
 */
syscall pipdelete(
	 pipid32		pip		/* ID of pipe to delete	*/
	)
{
	struct	pipent	*pipptr;
	intmask mask;				/* interrupt mask				*/

	mask = disable();			/* disable interrupts at start of function	*/
	
	if(isbadpip(pip)) {
		restore(mask);			/* restore interrupts before error return	*/
		return (pipid32) (SYSERR);
	}
	
	pipptr = &piptab[pip];
	
	if(pipptr->pipstate == PIPE_FREE) {
		restore(mask);			/* restore interrupts before error return	*/
		return (pipid32) (SYSERR);
	}
	
	if(pipptr->owner != (pid32)getpid()) {	/* make sure only owner can delete the pipe	*/
		restore(mask);			/* restore interrupts before error return	*/
		return (pipid32) (SYSERR);
	}

	pipptr->pipstate = PIPE_FREE;
	memset(pipptr->buff, '\0', PIPE_SIZE);
	pipptr->owner = -1;	
	pipptr->reader = -1;
	pipptr->writer = -1;
	pipcount--;
	
	semdelete(pipptr->emptySem);
	semdelete(pipptr->fullSem);

	restore(mask);				/* restore interrupts before normal return	*/
	return OK;		
}
