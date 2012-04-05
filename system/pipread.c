/* pipread.c - pipread */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  pipread  -  Read data from a connected pipe specified by pipe ID
The system call reads up to len bytes from the connected pipe and saves it in buf. If there are no len bytes in the pipe, it reads as many available and returns. The system call returns the actual number of bytes read or SYSERR, if the read is unsuccessful. The calling process blocks if there is no data to be read from a connected pipe. Note that only reader process can read from the pipe. 
 *------------------------------------------------------------------------
 */
syscall pipread(
	 pipid32		pip,		/* ID of pipe to read				*/
	 char*			buf,		/* pointer to buffer where data is written 	*/
	 uint32			len		/* length of data to be read			*/
	)
{	
	intmask mask;				/* interrupt mask				*/
	struct 	pipent	*pipptr;		/* pointer to pipe entry			*/
	int 	length = 0;

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
	
	/* make sure of the process */
	if(pipptr->owner == PR_FREE || pipptr->reader == PR_FREE || pipptr->writer == PR_FREE) {
		restore(mask);
		return (pipid32) (SYSERR);
	}
	
	if(pipptr->reader != (pid32)getpid()) {	/* check that it is the reader that reads	*/
		restore(mask);
		return (pipid32) (SYSERR);
	}
	
	
// 	kprintf("[READ]come\r\n");
	for(length = 0 ; length < len ; length++){
// 		kprintf("[READ]here\n\r");
// 		
		wait(pipptr->emptySem);
		
		buf[length] = pipptr->buff[pipptr->head];
		
// 		kprintf("reading this char : %c\n\r", buf[length]);
// 		kprintf("head before : %d\n\r", pipptr->head);
		
		pipptr->head = (pipptr->head+1) % 256; // so it automatically reset to front if the it reaches the end
		 
		
// 		kprintf("head now : %d\n\r", pipptr->head);
		
		signal(pipptr->fullSem);
	}

	restore(mask);				/* restore interrupts before normal return	*/
	return length;		
}
