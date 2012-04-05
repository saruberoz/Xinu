/* pipwrite.c - pipwrite */

#include <xinu.h>

uint32	pipbufflen2(byte	*buf);

/*------------------------------------------------------------------------
 *  pipwrite  -  Write data to the bounded buffer of a connected pipe
It takes as arguments the pipe ID, a pointer to the buffer from which data is to be written and the length of data to be written. The call returns SYSERR if the pipe is not in connected state. Otherwise, the call returns the number of bytes written to the pipe. If the bounded-buffer is full and there is no room for additional data to be written, the calling process needs is blocked. (Hint: use Xinu's semaphore primitives). If there is some space for data to be written, the system call copies the data in the available space from buf to the pipe (bounded-buffer) and returns the number of bytes written. Remember, that the actual number of bytes written to the pipe may be less than len. Note that only writer process can write to the pipe. 
 *------------------------------------------------------------------------
 */
syscall pipwrite(
	 pipid32		pip,		/* ID of pipe to delete					*/
	 char*			buf,		/* pointer to buffer where data is going to be written	*/
	 uint32			len		/* length of data to be written				*/
	)
{	
	intmask mask;				/* interrupt mask					*/
	struct 	pipent	*pipptr;		/* pointer to pipe entry				*/
	int 	length;
	//int 	walk;
	//int 	count;

	mask = disable();			/* disable interrupts at start of function		*/
	
	if(isbadpip(pip)) {
		restore(mask);			/* restore interrupts before error return		*/
		return (pipid32) (SYSERR);
	}
	
	pipptr = &piptab[pip];
	
	if(pipptr->pipstate != PIPE_CONNECTED){	/* make sure that it is the correct pipe		*/
		restore(mask);			/* restore interrupts before error return		*/
		return (pipid32) (SYSERR);
	}
	
	/* make sure of the process */
	if(pipptr->owner == PR_FREE || pipptr->reader == PR_FREE || pipptr->writer == PR_FREE) {
		restore(mask);
		return (pipid32) (SYSERR);
	}
	

	if(pipptr->writer != (pid32)getpid()) {	/* check that the writer is the one who is writing	*/
		restore(mask);
		return (pipid32) (SYSERR);
	}
	
// 	kprintf("[WRITE]come\r\n");
	
// 	kprintf("len : %d\r\n", len);
	for(length = 0 ; length < len ; length++) {
// 		kprintf("[WRITE]here\n\r");
		
		wait(pipptr->fullSem);
		
		pipptr->buff[pipptr->tail] = buf[length];
// 		kprintf("writing this char : %c\n\r", pipptr->buff[pipptr->tail]);
// 		kprintf("tail before : %d\n\r", pipptr->tail);
		
		pipptr->tail = (pipptr->tail+1) %256;
		
// 		kprintf("tail now : %d\n\r", pipptr->tail);
// 		kprintf("length now : %d\n\r", length);
		
		signal(pipptr->emptySem);
	}

	restore(mask);				/* restore interrupts before normal return		*/
	return length;
}
