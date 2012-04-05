/* sched.h */

/* Constants and variables related to deferred rescheduling */

#define	DEFER_START	1	/* start deferred rescehduling		*/
#define	DEFER_STOP	2	/* stop  deferred rescehduling		*/

/*CS 354 Spring 2012*/
/*Lab 2: Round Robin Scheduling*/
/*Created by : Wilson Sumanang
  Date       : 12 February 2012*/

#define ROUND_ROBIN	1	/* follow round robin scheme		*/

/* Structure that collects items related to deferred rescheduling	*/

struct	defer	{
	int32	ndefers;	/* number of outstanding defers 	*/
	bool8	attempt;	/* was resched called during the	*/
				/*   deferral period?			*/
};

extern	struct	defer	Defer;
