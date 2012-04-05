/* pipconnect.c - pipconnect */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipconnect  -  Connect two processes to an existing pipe
It takes as its arguments a pipe ID, a process ID for one end, and a process ID for the other end. The system call returns OK if the pipe is successful connected with two processes. In any case, if the arguments are invalid, the pipe was already connected to other processes, or the state of the pipe does not permit connection, the system call returns SYSERR. Note that only the owner of the pipe can call connect. If a non-owner tries to delete, then SYSERR needs to be returned. 
 *------------------------------------------------------------------------
 */
syscall pipconnect(
	 pipid32		pip,		/* ID of pipe to connect			*/
	 pid32			end1,		/* process ID for one end 			*/
	 pid32			end2		/* process ID for another end 			*/
	)
{	
	intmask mask;				/* interrupt mask				*/
	struct	pipent	*pipptr;		/* pointer to pipe entry			*/
	struct	procent	*prptr;			/* pointer to proc entry			*/
	struct	procent *prptr2;

	mask = disable();			/* disable interrupts at start of function	*/
	
	/* check the validity for both process id */
	if(isbadpid(end1) || (end1 == NULLPROC)|| isbadpid(end2) || (end2 == NULLPROC)) {
		restore(mask);			/* restore interrupts before error return	*/
		return (pid32) (SYSERR);
	}

	prptr = &proctab[end1];
	prptr2 = &proctab[end2];

	if((prptr->prstate == PR_FREE) || (prptr2->prstate == PR_FREE)){
		restore(mask);			/* restore interrupts before error return	*/
		return (pid32) (SYSERR);
	}
	
	if(isbadpip(pip)) {
		restore(mask);			/* restore interrupts before error return	*/
		return (pipid32) (SYSERR);
	}
	   
	pipptr = &piptab[pip];
	
	if(pipptr->pipstate != PIPE_USED) {	/* make sure that it is the correct pipe	*/
		restore(mask);			/* restore interrupts before error return	*/
		return (pipid32) (SYSERR);
	}
	
	if(pipptr->owner != (pid32)getpid()) {	/* make sure only owner can connect to the pipe	*/
		restore(mask);			/* restore interrupts before error return	*/
		return (pipid32) (SYSERR);
	}
	
	pipptr->pipstate = PIPE_CONNECTED;
	pipptr->reader = end1;
	pipptr->writer = end2;
	kprintf("-------Successfull Connecting Pipe-------\n\r");
	
	restore(mask);				/* restore interrupts before normal return	*/
	return OK;
}
