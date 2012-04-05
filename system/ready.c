/* ready.c - ready */

/*CS 354 Spring 2012*/
/*Lab 2: Round Robin Scheduling*/
/*Created by : Wilson Sumanang
  Date       : 12 February 2012*/

#include <xinu.h>

qid16	readylist;			/* index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid,		/* ID of process to make ready	*/
	  bool8		resch		/* reschedule afterward?	*/
	)
{
	register struct procent *prptr;

	int rrChecker = 1 ; 	/* variable to check if round robin should run */
	
	if (isbadpid(pid)) {
		return(SYSERR);
	}

	/* Set process state to indicate ready and add to ready list */
	
	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	if (rrChecker != 1) {
		insert(pid, readylist, prptr->prprio);
	} else if (rrChecker == ROUND_ROBIN) {
		insert(pid, readylist, prptr->prprio);
	}

	if (resch == RESCHED_YES) {
		resched();
	}
	return OK;
}
