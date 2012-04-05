/* pipe.h - creating an interprocess communication */

/*CS 354 Spring 2012*/
/*Lab 3: Interprocess Communication Using Bounded Buffers In Xinu */
/*Created by : Wilson Sumanang
  Date       : 26 February 2012*/

/* Maximum number of pipe in the system */
#ifndef NPIPE
#define	NPIPE		10
#endif		

/* Pipe state constants */
#define	PIPE_FREE		0	/* pipe has not been allocated, can't be read/write			*/
#define PIPE_USED		1	/* pipe has been created but no process is connected to the pipe	*/
#define PIPE_CONNECTED		2	/* pipe has been connected to two process				*/

/* Default pipe buffer size */
#define PIPE_SIZE		256	/* pipe fixed size buffer of 256 bytes	*/

/* Inline code to check pipe ID (assumes interrupts are disabled)	*/
#define	isbadpip(x)	( ((pipid32)(x) < 0) || \
			  ((pipid32)(x) >= NPIPE))

/* Definition of the pipe entry */
struct pipent {
	uint16	pipstate;		/* pipe state : PIPE_FREE, etc.		*/
	pid32	owner;			/* owner of the pipe			*/
	pid32	reader;			/* reader of the pipe			*/
	pid32	writer;			/* writer to the pipe			*/
	sid32	emptySem;		/* semaphore when buffer is empty	*/
	sid32	fullSem;		/* semaphore when buffer is full	*/
	byte	buff[PIPE_SIZE];	/* pipe buffer				*/
	int	head;
	int	tail;
};

extern	struct	pipent piptab[];	/* array of pipes			*/
extern	int32	pipcount;		/* currently active pipes		*/
