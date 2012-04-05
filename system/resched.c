/* resched.c - resched */

/*CS 354 Spring 2012*/
/*Lab 2: Round Robin Scheduling*/
/*Created by : Wilson Sumanang
  Date       : 12 February 2012*/

#include <xinu.h>

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* assumes interrupts are disabled	*/
{
	int rrChecker = 1 ; 	/* variable to check if round robin should run */

	struct procent *ptold;	/* ptr to table entry for old process	*/
	struct procent *ptnew;	/* ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */
	
	ptold = &proctab[currpid];

	/* existing scheme */
	if (rrChecker != 1){
		if (ptold->prstate == PR_CURR) {  /* process remains running */
			if (ptold->prprio > firstkey(readylist)) {
				return;
			}

			/* Old process will no longer remain current */

			ptold->prstate = PR_READY;
			insert(currpid, readylist, ptold->prprio);
		}
	} else if (rrChecker == ROUND_ROBIN) {
		if (ptold->prstate == PR_CURR) {  /* process remains running */
			ptold->prstate = PR_READY;/* change process state to ready state */
			insert(currpid, readylist, ptold->prprio);
		}
	}

	/* Force context switch to highest priority ready process */
	
	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}
