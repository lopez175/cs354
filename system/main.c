/*  main.c  - main */

#include <xinu.h>

process	main(void)
{

	/*TESTING PART 3 */
	long x = 200;
	
	//Test host2net
	long net = host2net(x);

	//Test host2netca
	net =host2netca(x);

	//Test host2neta
	net =host2neta(x);

	/*TEST PART 4*/
	struct	procent *prptr;		
	
	prptr = &proctab[currpid];
	char *ptrtop;
	asm(	"movl   %%esp, %0;"
		:"=r"(ptrtop)
                :
                :"%esp"
	);
	kprintf("1. main process before appl1():\n");
	kprintf("Base of the stack : Address - 0x%08X, Value - 0x%08X\n",prptr->prstkbase, *(int *)(prptr->prstkbase));
	kprintf("Top of the stack : Address - 0x%08X, Value - 0x%08X\n\n",ptrtop, *(int *)(ptrtop));
	
	//Should comment out for attacker's and victim's processes are adjacent.
	resume(create((int *)appl1, 2048, INITPRIO, "appl1", 0));	

	//Extra credit! Works!
	//gocreate((int *)appl1, 2048, INITPRIO, "appl1", 0);
	
	/*PART 5*/

	resume(create(stackoverflowA, 2048, 10, "attacker", 0));
	resume(create(stackoverflowB, 2048, 15, "victim", 0));
	
	sleep(3);	
	
	//Extra credit
}
