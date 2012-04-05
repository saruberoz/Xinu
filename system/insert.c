/* insert.c - insert */

/*CS 354 Spring 2012*/
/*Lab 2: Round Robin Scheduling*/
/*Created by : Wilson Sumanang
  Date       : 12 February 2012*/

#include <xinu.h>

/*------------------------------------------------------------------------
 *  insert  -  Insert a process into a queue in descending key order
 *------------------------------------------------------------------------
 */
status	insert(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* key for the inserted process	*/
	)
{
	int16	curr;			/* runs through items in a queue*/
	int16	prev;			/* holds previous node index	*/
	int tail;			/* holds tails node */

	int rrChecker = 1 ; 	/* variable to check if round robin should run */

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}
	if (rrChecker != 1) {
		curr = firstid(q);
		while (queuetab[curr].qkey >= key) {
			curr = queuetab[curr].qnext;
		}

		/* insert process between curr node and previous node */

		prev = queuetab[curr].qprev;	/* get index of previous node	*/
		queuetab[pid].qnext = curr;
		queuetab[pid].qprev = prev;
		queuetab[pid].qkey = key;
		queuetab[prev].qnext = pid;
		queuetab[curr].qprev = pid;
		
	} else if (rrChecker == ROUND_ROBIN) {

		tail = queuetail(q);
		prev = queuetab[tail].qprev;

		queuetab[pid].qnext  = tail;	/* insert just before tail node	*/
		queuetab[pid].qprev  = prev;
		queuetab[pid].qkey = key;
		queuetab[prev].qnext = pid;
		queuetab[tail].qprev = pid;
		
	}
	return OK;
}
